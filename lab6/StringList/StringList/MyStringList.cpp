#include "stdafx.h"
#include "MyStringList.h"

typedef CListIterator ListIterator;
typedef const CListIterator ConstListIterator;

bool CListIterator::operator!=(CListIterator const & other) const
{
	return m_node != other.m_node;
}

bool CListIterator::operator==(CListIterator const & other) const
{
	return m_node == other.m_node;
}

CListIterator & CListIterator::operator++()
{
	m_node = (m_isReverse ? m_node->prev : m_node->next.get());
	return *this;
}

CListIterator CListIterator::operator++(int)
{
	auto returned = *this;
	++(*this);
	return returned;
}

CListIterator & CListIterator::operator--()
{
	m_node = (m_isReverse ? m_node = m_node->next.get() : m_node = m_node->prev);
	return *this;
}

CListIterator CListIterator::operator--(int)
{
	auto returned = *this;
	--(*this);
	return returned;
}

std::string & CListIterator::operator*() const
{
	return m_node->data;
}

std::string * CListIterator::operator->() const
{
	return &m_node->data;
}

SNode * CListIterator::get() const
{
	return m_node;
}

CMyStringList::CMyStringList(CMyStringList & other)
{
	*this = other;
}

CMyStringList & CMyStringList::operator=(CMyStringList & other)
{
	if (this != &other) // защита от неправильного самоприсваивания
	{
		CMyStringList tmp;
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

CMyStringList::~CMyStringList()
{
	Clear();
}

size_t CMyStringList::GetSize()
{
	return m_size;
}

void CMyStringList::PushBack(const std::string & data)
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

void CMyStringList::PushFront(const std::string & data)
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

void CMyStringList::Clear()
{
	while (m_lastNode)
	{
		m_lastNode->next = nullptr;
		m_lastNode = m_lastNode->prev;
	}
	m_firstNode = nullptr;
	m_size = 0;
}

bool CMyStringList::IsEmpty() const
{
	return m_size == 0u;
}

std::string & CMyStringList::GetBackElement()
{
	return m_lastNode->data;
}

const std::string & CMyStringList::GetBackElement() const
{
	return m_lastNode->data;
}

std::string & CMyStringList::GetFrontElement()
{
	return m_firstNode->data;
}

const std::string & CMyStringList::GetFrontElement() const
{
	return m_firstNode->data;
}

ListIterator CMyStringList::begin()
{
	return ListIterator(m_firstNode.get(), false);
}

ListIterator CMyStringList::end()
{
	return ListIterator(m_lastNode->next.get(), false);
}

const ConstListIterator CMyStringList::cbegin() const
{
	return ConstListIterator(m_firstNode.get(), false);
}

const ConstListIterator CMyStringList::cend() const
{
	return ConstListIterator(m_lastNode->next.get(), false);
}

ListIterator CMyStringList::rbegin()
{
	return ListIterator(m_lastNode, true);
}

ListIterator CMyStringList::rend()
{
	return ListIterator(m_firstNode->prev, true);
}

const ConstListIterator CMyStringList::crbegin() const
{
	return ConstListIterator(m_lastNode, true);
}

const ConstListIterator CMyStringList::crend() const
{
	return ConstListIterator(m_firstNode->prev, true);
}

void CMyStringList::Insert(const ListIterator & it, std::string data)
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

void CMyStringList::Erase(const ListIterator & it)
{
	if (it == begin())
	{
		if (m_size == 1)
		{
			Clear();
			return;
		}
		it.get()->next.get()->prev = nullptr;
		m_firstNode = std::move(it.get()->next);
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
