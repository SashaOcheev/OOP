#pragma once
#include "stdafx.h"
#include <string>
#include <memory>

template<typename T>
class CMyList
{
	struct SNode
	{
		SNode(const T & data, SNode * prev, std::unique_ptr<SNode> && next) : data(data), prev(prev), next(std::move(next)) {}

		T data;
		SNode *prev;
		std::unique_ptr<SNode> next;
	};

	template<typename U>
	class CListIterator : public std::iterator <std::bidirectional_iterator_tag, U>
	{
	public:
		CListIterator(SNode* value, bool isReverse)
			: m_node(value)
			, m_isReverse(isReverse)
		{
		}

		friend class CMyList<T>;

		bool operator!=(CListIterator const& other) const
		{
			return m_node != other.m_node;
		}
		bool operator==(CListIterator const& other) const
		{
			return m_node == other.m_node;
		}

		U & operator*() const
		{
			return m_node->data;
		}

		CListIterator& operator++()
		{
			if (m_isReverse)
			{
				m_node = m_node->prev;
			}
			else
			{
				m_node = m_node->next.get();
			}
			return *this;
		}
		CListIterator& operator--()
		{
			if (m_isReverse)
			{
				m_node = m_node->next.get();
			}
			else
			{
				m_node = m_node->prev;
			}
			return *this;
		}

		SNode* operator->()const
		{
			return m_node;
		}

	private:

		SNode* m_node = nullptr;
		bool m_isReverse = b false;
	};

	typedef CListIterator<T> ListIterator;
	typedef CListIterator<const T> ConstListIterator;

public:
	CMyList() = default;

	//copy constructor
	CMyList(CMyList & other)
	{
		*this = other;
	}

	//copy assignment
	CMyList& operator=(CMyList & other)
	{
		if (this != &other) // защита от неправильного самоприсваивания
		{
			CMyList tmp;
			for (auto const & elem : other)
			{
				tmp.PushBack(elem);
			}
			std::swap(m_firstNode, tmp.m_firstNode);
			std::swap(m_lastNode, tmp.m_lastNode);
			m_size = tmp.m_size;
		}
		// по соглашению всегда возвращаем *this
		return *this;
	}

	~CMyList()
	{
		Clear();
	}

	size_t GetSize()
	{
		return m_size;
	}

	void PushBack(const T & data)
	{
		auto newNode = std::make_unique<SNode>(data, m_lastNode, nullptr);
		SNode *newLastNode = newNode.get();
		if (m_lastNode)
		{
			m_lastNode->next = std::move(newNode);
		}
		else
		{
			m_firstNode = std::move(newNode);
		}
		m_lastNode = newLastNode;
		m_lastNode->next = nullptr;
		++m_size;
	}
	void PushFront(const T & data)
	{
		auto newNode = std::make_unique<SNode>(data, nullptr, std::move(m_firstNode));
		if (newNode->next)
		{
			newNode->next->prev = newNode.get();
		}
		else
		{
			m_lastNode = newNode.get();
		}
		m_firstNode = std::move(newNode);
		m_firstNode->prev = nullptr;
		m_size++;
	}

	void Clear()
	{
		while (m_lastNode)
		{
			m_lastNode->next = nullptr;
			m_lastNode = m_lastNode->prev;
		}
		m_firstNode = nullptr;
		m_size = 0;
	}

	bool IsEmpty() const
	{
		return m_size == 0u;
	}

	T & GetBackElement()
	{
		return m_lastNode->data;
	}
	const T & GetBackElement() const
	{
		return m_lastNode->data;
	}
	T & GetFrontElement()
	{
		return m_firstNode->data;
	}
	const T & GetFrontElement() const
	{
		return m_firstNode->data;
	}

	ListIterator begin()
	{
		return ListIterator(m_firstNode.get(), false);
	}
	ListIterator end()
	{
		return ListIterator(m_lastNode->next.get(), false);
	}
	const ConstListIterator cbegin() const
	{
		return ConstListIterator(m_firstNode.get(), false);
	}
	const ConstListIterator cend() const
	{
		return ConstListIterator(m_lastNode->next.get(), false);
	}
	ListIterator rbegin()
	{
		return ListIterator(m_lastNode, true);
	}
	ListIterator rend()
	{
		return ListIterator(m_firstNode->prev, true);
	}
	const ConstListIterator crbegin() const
	{
		return ConstListIterator(m_lastNode, true);
	}
	const ConstListIterator crend() const
	{
		return ConstListIterator(m_firstNode->prev, true);
	}

	void Insert(const ListIterator & it, T data)
	{
		if (it == begin())
		{
			PushFront(data);
		}
		else if (it == end())
		{
			PushBack(data);
		}
		else
		{
			auto node = std::make_unique<SNode>(data, it->prev, std::move(it->prev->next));
			it->prev = std::move(node.get());
			node->prev->next = std::move(node);
		}
	}
	void Erase(const ListIterator & it)
	{
		if (m_size == 1)
		{
			Clear();
			return;
		}

		if (it == begin())
		{
			it->next->prev = nullptr;
			m_firstNode = move(it->next);
		}
		else if (it->data == GetBackElement())
		{
			it->prev->next = nullptr;
			m_lastNode = std::move(it->prev);
		}
		else
		{
			it->next->prev = std::move(it->prev);
			it->prev->next = std::move(it->next);
		}

		if (m_size > 0)
		{
			m_size--;
		}
	}

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_firstNode = nullptr;
	SNode * m_lastNode = nullptr;
};