//
// Copyright (c) 2014 Krzysztof Jusiak (krzysztof at jusiak dot net)
// // Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_DI_CORE_ANY_TYPE_HPP
#define BOOST_DI_CORE_ANY_TYPE_HPP

#include "boost/di/aux_/memory.hpp"
#include "boost/di/aux_/type_traits.hpp"

namespace boost { namespace di { namespace core {

template<
    class TParent = aux::none_t
  , class TInjector = aux::none_t
  , class TProvider = aux::none_t
  , class TPolicies = aux::none_t
>
struct any_type {
    template<class T>
    using is_not_same_t = std::enable_if_t<
        !std::is_same<aux::make_plain_t<T>, aux::make_plain_t<TParent>>::value
    >;

    template<class T, class = is_not_same_t<T>>
    operator T() noexcept {
        return creator_.template create_impl<T, TParent>(provider_, policies_);
    }

    const TInjector& creator_;
    const TProvider& provider_;
    const TPolicies& policies_;
};

template<class>
struct is_any_type : std::false_type { };

template<class... TArgs>
struct is_any_type<any_type<TArgs...>> : std::true_type { };

}}} // namespace boost::di::core

#endif

