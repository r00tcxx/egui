#pragma once
#include <string>
#include <fstream>
#include <stdexcept>
#include <list>
#include <variant>
#include <optional>
#include <vector>
#include <map>
#include <functional>

#define throw_if(cond, msg) \
do{ if(cond) throw std::runtime_error(msg); } while (0);

namespace enigma::eul {
	using exception = std::runtime_error;
	using size_t = std::size_t;

	class value {
	public:
		value() {}
	};

	template<class _Elem>
	class parser {
		using _ifstream = std::basic_ifstream<_Elem>;
		using _string = std::basic_string<_Elem>;
		using _size_t = std::size_t;

		enum _token_type {
			unknown = 0,
			node,
			lb, rb,
			prop_name,
			prop_val,
			colon,
			scolon
		};

		class _token {
		protected:
			_token_type _t;
			_size_t _line, _offset;
			_string _val;
		public:
			_token(_token_type t, const _size_t line, const _size_t offset, const _string& val)
				: _t(t), _line(line), _offset(offset), _val(val) {}

		};

		class _reader {
			_ifstream _in;
			_size_t _size{ 0 }, _pos{ 0 }, _line{ 1 }, _offset{ 0 };
		public:
			_reader(const _string& file) noexcept(false) {
				_in.open(file, std::ios::in | std::ios::binary);
				throw_if(!_in, "Load eul file failed.");
				_in.seekg(0, std::ios::end);
				_size = _in.tellg();
				_in.seekg(std::ios::beg);
			}

			~_reader() {
				if (_in)_in.close();
			}

			_Elem getc() {
				while (++_pos <= _size && ++_offset) {
					auto tmp = _in.get();
					if ('\n' == tmp && ++_line + (_offset = 0)) continue;
					else return tmp;
				}
				return EOF;
			}

			std::vector<_Elem> get_until(_Elem c) {
				std::vector<_Elem> buf;
				_Elem tmp{ 0 };
				while (!eof() && c != (tmp = getc())) 
					buf.push_back(tmp);
				return std::move(buf);
			}

			inline auto line() const { return _line; }
			inline auto offset() const { return _offset; }
			inline auto total() const { return _size; }
			inline bool eof() const { return _pos >= _size; }
		};

		std::list<std::shared_ptr<_token>> _tokens;

	public:
		value parse(const _string& file) {
			_reader r(file);
			if (!r.total()) return value{};
			auto prev_token = new_token(r);
			while (!r.eof()) {
				auto c = r.getc();
				if ('{' == c) {
			//		prev_token->type = _token::_type::node;
					_tokens.push_back(prev_token);
					_tokens.push_back(new_token(r, _token_type::lb));
				}

			}

		}

	protected:
		std::shared_ptr<_token> new_token(
			_reader& r, 
			_token_type t = _token_type::unknown) {
			return std::make_shared<_token>(new _token( t, r.line(), r.offset(), "" ));
		}
	};
}
