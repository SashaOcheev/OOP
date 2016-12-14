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

		CListIterator& operator++()
		{
			m_node = (m_isReverse ? m_node->prev : m_node->next.get());
			return *this;
		}

		CListIterator operator++(int)
		{
			auto returned = *this;
			++(*this);
			return returned;
		}

		CListIterator& operator--()
		{
			m_node = (m_isReverse ? m_node = m_node->next.get() : m_node = m_node->prev);
			return *this;
		}

		CListIterator operator--(int)
		{
			auto returned = *this;
			--(*this);
			return returned;
		}

		U& operator*() const
		{
			return m_node->data;
		}

		U* operator->() const
		{
			return &m_node->data;
		}

	private:
		SNode* get()const
		{
			return m_node;
		}

		SNode* m_node = nullptr;
		bool m_isReverse = false;
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
			auto node = std::make_unique<SNode>(data, it.get()->prev, std::move(it.get()->prev->next));
			it.get()->prev = node.get();
			node->prev->next = std::move(node);
		}
	}

	void Erase(const ListIterator & it)
	{
		if (it == begin())
		{
			if (m_size == 1)
			{
				Clear();
				return;
			}
			it.get()->next.get()->prev = nullptr;
			m_firstNode = move(it.get()->next);
		}
		else if (it.get()->data == GetBackElement())
		{
			it.get()->prev->next = nullptr;
			m_lastNode = it.get()->prev;
		}
		else
		{
			it.get()->next->prev = it.get()->prev;
			it.get()->prev->next = std::move(it.get()->next);
		}

		--m_size;
	}

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_firstNode = nullptr;
	SNode * m_lastNode = nullptr;
};