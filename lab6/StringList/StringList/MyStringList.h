#pragma once
#include "stdafx.h"
#include <string>
#include <memory>

struct SNode
{
	SNode(const std::string & data, SNode * prev, std::unique_ptr<SNode> && next) : data(data), prev(prev), next(std::move(next)) {}

	std::string data;
	SNode *prev;
	std::unique_ptr<SNode> next;
};


class CListIterator : public std::iterator <std::bidirectional_iterator_tag, std::string>
{
public:

	friend class CMyStringList;

	bool operator!=(CListIterator const& other) const;
	bool operator==(CListIterator const& other) const;

	CListIterator& operator++();
	CListIterator operator++(int);
	CListIterator& operator--();
	CListIterator operator--(int);
	std::string& operator*() const;
	std::string* operator->() const;

private:
	CListIterator(SNode* value, bool isReverse)
		: m_node(value)
		, m_isReverse(isReverse)
	{
	}

	SNode* get()const;

	SNode* m_node = nullptr;
	bool m_isReverse = false;
};


class CMyStringList
{
	typedef CListIterator ListIterator;
	typedef const CListIterator ConstListIterator;

public:
	CMyStringList() = default;
	//copy constructor
	CMyStringList(CMyStringList & other);
	//copy assignment
	CMyStringList& operator=(CMyStringList & other);
	~CMyStringList();

	size_t GetSize();
	void PushBack(const std::string & data);
	void PushFront(const std::string & data);
	void Clear();
	bool IsEmpty() const;
	std::string & GetBackElement();
	const std::string & GetBackElement() const;
	std::string & GetFrontElement();
	const std::string & GetFrontElement() const;
	ListIterator begin();
	ListIterator end();
	const ConstListIterator cbegin() const;
	const ConstListIterator cend() const;
	ListIterator rbegin();
	ListIterator rend();
	const ConstListIterator crbegin() const;
	const ConstListIterator crend() const;
	void Insert(const ListIterator & it, std::string data);
	void Erase(const ListIterator & it);

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_firstNode = nullptr;
	SNode * m_lastNode = nullptr;
};