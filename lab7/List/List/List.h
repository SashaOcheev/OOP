#pragma once
#include <memory>
#include <iterator>
#include <algorithm>

template<class T>
class CList
{
	struct SNode
	{
		SNode(const T &data, T *previous, std::unique_ptr<T> &&next)
			: m_data(data)
			, m_previous(std::move(previous))
			, m_next(next)
		{}

		T m_data;
		T *m_previous = nullptr;
		std::unique_ptr<T> m_next = nullptr;
	};

	template<class U>
	class CIterator : public std::iterator<std::bidirectional_iterator_tag, U>
	{
		friend class CList;
	private:
		

	public:
		bool operator!=(CIterator const& other) const
		{
			return m_node != other.m_node;
		}

		bool operator==(CIterator const& other) const
		{
			return m_node == other.m_node;
		}

		U &operator*() const
		{
			return (*m_node).data;
		}

		U *operator->() const
		{
			return  m_node;
		}

		CIterator &operator++()
		{
			m_node = (*m_node).next.get();
			return this;
		}

		CIterator &operator++(int)
		{
			SNode *temp = m_node;
			m_node = (*m_node).next.get();
			return temp;
		}

		CIterator &operator--()
		{
			m_node = (*m_node).previous;
			return this;
		}

		CIterator &operator--(int)
		{
			SNode *temp = m_node;
			m_node = (*m_node).previous;
			return temp;
		}
	private:
		CIterator(SNode* node)
			: m_node(node)
		{
		}

		SNode *m_node = nullptr;
	};

	typedef CIterator<T> iterator;
	typedef CIterator<const T> const_iterator;

public:
	CList() = default;

	size_t size() const
	{
		return m_size;
	}

	//CList(const CList&)
	//{
	//	COPY CONSTUCTOR
	//}

	void push_back()
	{
		
	}

	bool empty() const
	{
		return m_size > 0;
	}

	iterator begin()
	{
		return iterator(m_begin.get());
	}

	iterator end()
	{
		return iterator(m_end->next.get());
	}

	const_iterator begin() const
	{
		return const_iterator(m_begin.get());
	}

	const_iterator end() const
	{
		return const_iterator(m_end->next.get());
	}

	~CList()
	{

	}

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_begin = nullptr;
	SNode *m_end = nullptr;
};