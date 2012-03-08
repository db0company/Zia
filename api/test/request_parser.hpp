/*
 * request_parser.hpp for zia
 * by lenorm_f
 */

#ifndef __REQUEST_PARSER_H__
#define __REQUEST_PARSER_H__

#include "request.hpp"

namespace zia { namespace http {
	template <typename T>
	class request_parser {
		typedef T buffer_type;
		typedef typename T::iterator buffer_iterator;
		typedef typename T::const_iterator buffer_const_iterator;

		enum eState {
			STATE_UNKOWN = -1,
			STATE_OVER = 0,
			STATE_STALLED,
		};

		// FIXME: all of this will be replaced with the conf's parsed
		// nodes
		struct parserNode {
			enum eType {
				NODE_UNKNOWN = -1,
				NODE_METHOD = 0,
				NODE_URI,
				NODE_HTTP_VERSION,
			};

			eType type;
			T value;
		};

		static eState parser(buffer_iterator &buffer_begin, buffer_const_iterator &end, parserNode &node) {
			for (; buffer_begin != end; ++buffer_begin) {
				;
			}

			return STATE_STALLED;
		}

		public:
		static method toMethod(T const &data) {
			return METHOD_UNKNOWN;
		}

		static IRequest<T> *unmarshal(T const &data) {
			T buffer = data;
			IRequest<T> *req = new Request(buffer);

			eState state;
			parserNode node;
			buffer_iterator buffer_begin = buffer.begin();
			buffer_const_iterator buffer_end = buffer.end();
			while ((state = parser(buffer_begin, buffer_end, node)) == STATE_STALLED) {
				switch (node.type) {
					case parserNode::eType::NODE_URI: req->setMethod(toMethod(node.value)); break;
					case parserNode::eType::NODE_HTTP_VERSION: break;
					default: break;
				}
			}

			return req;
		}
	};
}}

#endif
