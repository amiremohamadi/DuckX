/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work wirh docx files.
 */

#ifndef DUCKXITERATOR_H
#define DUCKXITERATOR_H

namespace duckx {
	template <class T>
	class Iterator {
	private:
		T* _obj = nullptr;

	public:
		Iterator() = default;
		Iterator(T& obj) : _obj(&obj) {}

		// We only care comparator against end.
		bool operator!=(const Iterator&) const { return _obj != nullptr; }

		// Check against the end
		void operator++() {
			_obj->next();
			if (!_obj->has_next()) {
				_obj = nullptr;
			}
		}

		auto operator*() const -> T & { return *_obj; }

		auto operator-> () const -> T* { return _obj; }
	};

	// Entry points for loops
	template <class T>
	auto begin(T& obj) { return Iterator<T>(obj); }
	template <class T>
	auto end(T&) { return Iterator<T>(); }
}

#endif