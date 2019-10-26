/*
 * Under MIT license
 * Author: Amir Mohamadi (@amiremohamadi)
 * DuckX is a free library to work wirh docx files.
 */

#ifndef DUCKXITERATOR_H
#define DUCKXITERATOR_H

namespace duckx
{
	template <class T>
	class Iterator
	{
	protected:
		T _obj{};
	public:
		Iterator() = default;

		explicit Iterator(T obj) : _obj(std::move(obj))
		{
		}

		bool operator!=(const Iterator& other) const
		{
			// Check if valid
			if (_obj.has_next() || other._obj.has_next())
			{
				return _obj.parent != other._obj.parent || _obj.current != other._obj.current;
			}
			return false;
		}

		bool operator==(const Iterator& other) const
		{
			return !((*this) != other);
		}

		// Check against the end
		Iterator& operator++() { _obj.next(); return *this;}

		auto operator*() const -> T const& { return _obj; }

		auto operator->() const -> T const* { return &_obj; }
	};

	// Entry point
	template <class T>
	auto begin(T obj)
	{
		return Iterator<T>(std::move(obj));
	}

	template <class T>
	auto end(T)
	{
		return Iterator<T>();
	}
} // namespace duckx

#endif
