#ifndef BITDEWY_SWITCHER_HPP_
#define BITDEWY_SWITCHER_HPP_

namespace bitdewy {
  
template <int index, int count, class dispatcher>
struct switcher {
  typename dispatcher::result_type
  operator()(const dispatcher& disp, int type) const {
    if (type == index) {
      return disp.template Case<index>();
    } else {
      return switcher<index + 1, count, dispatcher>()(disp, type);
    }
  }
};

template <int count, class dispatcher>
struct switcher<count, count, dispatcher> {
  typename dispatcher::result_type
  operator()(const dispatcher& disp, int type) const {
    return disp.Default(type);
  }
};

template <int count, class dispatcher>
typename dispatcher::result_type
Switch(const dispatcher& disp, int type) {
  return switcher<0, count, dispatcher>()(disp, type);
}

}  // namespace bitdewy

#endif  // BITDEWY_SWITCHER_HPP_
