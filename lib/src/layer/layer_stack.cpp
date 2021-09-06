#include "phosphorus/layer/layer_stack.h"

#include <ranges>
#include <fmt/core.h>

#include "phosphorus/core/error.h"

namespace ph
{
    LayerStack::~LayerStack() noexcept
    {
        try
        {
            for (Layer& layer : *this | std::views::reverse)
                layer.on_detach();
        }
        PH_ENGINE_CATCH_FATAL;
    }

    Layer& LayerStack::add_layer(Layer layer)
    {
        Layer& res = *layers_.emplace(layers_.begin() + overlay_index_, std::move(layer));
        res.on_attach();
        overlay_index_++;
        return res;
    }

    Layer& LayerStack::add_overlay(Layer layer)
    {
        Layer& res = layers_.emplace_back(std::move(layer));
        res.on_attach();
        return res;
    }

    Layer LayerStack::remove_layer(const void* ptr)
    {
        const auto iter = std::ranges::find(layers_, ptr, [](const Layer& layer) { return layer.data(); });
        if (iter == layers_.end())
            throw_exception(fmt::format("Cannot find layer with pointer at {:x} in the layer stack", ptr), true);
        if (iter - layers_.begin() < overlay_index_) overlay_index_--;
        Layer layer = std::move(*iter);
        layers_.erase(iter);
        layer.on_detach();
        return layer;
    }

    Layer LayerStack::remove_layer(const std::string_view name)
    {
        const auto iter = std::ranges::find(layers_, name, &Layer::name);
        if (iter == layers_.end())
            throw_exception(fmt::format("Cannot find layer with name {:x} in the layer stack", name), true);
        if (iter - layers_.begin() < overlay_index_) overlay_index_--;
        Layer layer = std::move(*iter);
        layers_.erase(iter);
        layer.on_detach();
        return layer;
    }
}
