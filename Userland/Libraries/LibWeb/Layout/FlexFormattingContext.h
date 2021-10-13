/*
 * Copyright (c) 2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/Layout/FormattingContext.h>

namespace Web::Layout {

struct FlexItem;

class FlexFormattingContext final : public FormattingContext {
public:
    FlexFormattingContext(Box& flex_container, FormattingContext* parent);
    ~FlexFormattingContext();

    virtual bool inhibits_floating() const override { return true; }

    virtual void run(Box&, LayoutMode) override;

private:
    bool has_definite_main_size(Box const&) const;
    bool has_definite_cross_size(Box const&) const;
    float specified_main_size(Box const&) const;
    float specified_cross_size(Box const&) const;
    bool has_main_min_size(Box const&) const;
    bool has_cross_min_size(Box const&) const;
    bool cross_size_is_absolute_or_resolved_nicely(NodeWithStyle const&) const;
    float specified_main_max_size(Box const&) const;
    float specified_cross_max_size(Box const&) const;
    float calculated_main_size(Box const&) const;
    bool is_cross_auto(Box const&) const;
    bool is_main_axis_margin_first_auto(Box const&) const;
    bool is_main_axis_margin_second_auto(Box const&) const;
    float specified_main_size_of_child_box(Box const& flex_container, Box const& child_box) const;
    float specified_main_min_size(Box const&) const;
    float specified_cross_min_size(Box const&) const;
    bool has_main_max_size(Box const&) const;
    bool has_cross_max_size(Box const&) const;
    float sum_of_margin_padding_border_in_main_axis(Box const&) const;

    void set_main_size(Box&, float size);
    void set_cross_size(Box&, float size);
    void set_offset(Box&, float main_offset, float cross_offset);
    void set_main_axis_first_margin(Box&, float margin);
    void set_main_axis_second_margin(Box&, float margin);

    void generate_anonymous_flex_items(Box& flex_container, Vector<FlexItem>&);

    struct AvailableSpace {
        float main { 0 };
        float cross { 0 };
    };
    AvailableSpace determine_available_main_and_cross_space(Box const& flex_container, bool& main_size_is_infinite, bool& main_is_constrained, bool& cross_is_constrained, float& main_min_size, float& main_max_size, float& cross_min_size, float& cross_max_size) const;

    bool is_row_layout() const { return m_flex_direction == CSS::FlexDirection::Row || m_flex_direction == CSS::FlexDirection::RowReverse; }

    CSS::FlexDirection m_flex_direction {};
};

}
