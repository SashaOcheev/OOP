#pragma once

#include <memory>

template <typename T>
class CMyList
{
private:
	struct Node
	{
		Node *prev;
		T data;
		std::unique_ptr<Node> next;

		Node(const T & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data)
			, prev(prev)
			, next(std::move(next))
		{
		}
	};

	template<typename U>
	class CIterator : std::iterator <std::bidirectional_iterator_tag, U>
	{
	public:
		friend CMyList<T>;

		CIterator(Node *node) :
			m_node(node)
		{
		}

		U& operator*()
		{
			
		}

		bool operator==(const CIterator &other) const
		{
			return  other.m_node == m_node;
		}

		bool operator!=(const CIterator &other) const
		{
			return other.m_node != m_node;
		}

		CIterator& operator++()
		{
			m_node = m_node->next.get()
			return *this;
		}

		CIterator& operator++(int)
		{
			auto returnIt = this;
			m_node = m_node->next.get();
			return *returnIt;
		}

		CIterator& operator--()
		{
			m_node = m_node->prev;
			return *this;
		}
		
		CIterator& operator--(int)
		{
			auto returnIt = this;
			m_node = m_node->prev;
			return *returnIt;
		}

	private:
		Node *m_node = nullptr;
	};

	typedef CIterator<T> Iterator;
	typedef CIterator<const T> ConstIterator;

public:
	CMyList() = default;

	size_t GetSize()
	{
		return m_size;
	}

	Iterator begin()
	{
		return Iterator(m_first);
	}

	ConstIterator begin() const
	{
		return ConstIterator(m_first);
	}

	Iterator end()
	{
		return Iterator(m_last);
	}

	ConstIterator end() const
	{
		return ConstIterator(m_last);
	}

private:
	std::unique_ptr<Node> m_first = nullptr;
	Node *m_last = nullptr;
	size_t m_size = 0;
};
