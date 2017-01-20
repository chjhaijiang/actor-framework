/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright (C) 2011 - 2016                                                  *
 * Dominik Charousset <dominik.charousset (at) haw-hamburg.de>                *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#ifndef CAF_DETAIL_INCOMING_STREAM_MULTIPLEXER_HPP
#define CAF_DETAIL_INCOMING_STREAM_MULTIPLEXER_HPP

#include <deque>
#include <cstdint>
#include <algorithm>
#include <unordered_map>

#include "caf/actor.hpp"
#include "caf/error.hpp"
#include "caf/local_actor.hpp"
#include "caf/stream_msg.hpp"

#include "caf/detail/stream_multiplexer.hpp"

namespace caf {
namespace detail {

// Forwards messages from local actors to a remote stream_serv.
class incoming_stream_multiplexer : public stream_multiplexer {
public:
  /// Allow `variant` to recognize this type as a visitor.
  using result_type = void;

  incoming_stream_multiplexer(local_actor* self, backend& service, actor& basp);

  void operator()(stream_msg& x);

  void operator()(stream_msg::open&);

  void operator()(stream_msg::ack_open&);

  void operator()(stream_msg::batch&);

  void operator()(stream_msg::ack_batch&);

  void operator()(stream_msg::close&);

  void operator()(stream_msg::abort&);

  void operator()(stream_msg::downstream_failed&);

  void operator()(stream_msg::upstream_failed&);

  template <class T>
  void operator()(stream_msg& x, T& y) {
    prepare_invoke(x);
    (*this)(y);
  }
};

} // namespace detail
} // namespace caf

#endif // CAF_DETAIL_INCOMING_STREAM_MULTIPLEXER_HPP
