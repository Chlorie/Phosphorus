#pragma once

#include <vector>

#include "layer.h"

namespace ph
{
    PH_SUPPRESS_EXPORT_WARNING
    class PH_API LayerStack final
    {
    public:
        using iterator = std::vector<Layer>::iterator;
        using const_iterator = std::vector<Layer>::const_iterator;
        using reverse_iterator = std::vector<Layer>::reverse_iterator;
        using const_reverse_iterator = std::vector<Layer>::const_reverse_iterator;

    private:
        ptrdiff_t overlay_index_ = 0;
        std::vector<Layer> layers_;

    public:
        LayerStack() = default;
        LayerStack(const LayerStack&) = delete;
        LayerStack(LayerStack&&) noexcept = default;
        LayerStack& operator=(const LayerStack&) = delete;
        LayerStack& operator=(LayerStack&&) noexcept = default;
        ~LayerStack() noexcept;

        template <typename LayerType, typename... Ts>
        Layer& emplace_layer(const std::string_view name, Ts&&... args)
        {
            return add_layer(Layer::create<LayerType>(name, std::forward<Ts>(args)...));
        }
        template <typename LayerType, typename... Ts>
        Layer& emplace_overlay(const std::string_view name, Ts&&... args)
        {
            return add_overlay(Layer::create<LayerType>(name, std::forward<Ts>(args)...));
        }

        Layer& add_layer(Layer layer);
        Layer& add_overlay(Layer layer);
        Layer remove_layer(const void* ptr);
        Layer remove_layer(std::string_view name);

        [[nodiscard]] auto begin() { return layers_.begin(); }
        [[nodiscard]] auto begin() const { return layers_.begin(); }
        [[nodiscard]] auto cbegin() const { return layers_.cbegin(); }
        [[nodiscard]] auto end() { return layers_.end(); }
        [[nodiscard]] auto end() const { return layers_.end(); }
        [[nodiscard]] auto cend() const { return layers_.cend(); }
        [[nodiscard]] auto rbegin() { return layers_.rbegin(); }
        [[nodiscard]] auto rbegin() const { return layers_.rbegin(); }
        [[nodiscard]] auto crbegin() const { return layers_.crbegin(); }
        [[nodiscard]] auto rend() { return layers_.rend(); }
        [[nodiscard]] auto rend() const { return layers_.rend(); }
        [[nodiscard]] auto crend() const { return layers_.crend(); }
    };
    PH_RESTORE_EXPORT_WARNING
}
