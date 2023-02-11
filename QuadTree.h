#ifndef QUADTREE_H
#define QUADTREE_H

#include <SFML/Graphics.hpp>

#include <memory>
#include <array>
#include <list>

struct rect{
sf::Vector2f pos;
sf::Vector2f size;

rect(const sf::Vector2f& p ={0.0f,0.0f}, const sf::Vector2f& s ={1.0f,1.0f}) :pos(p), size(s){}
bool contains(const sf::Vector2f& p) const{
	return(p.x>=pos.x && p.x<=pos.x+size.x && p.y>=pos.y && p.y <= pos.y+size.y);
}
bool contains(const rect& r) const{
return (r.pos.x>=pos.x &&
         r.pos.x+r.size.x<=pos.x+size.x &&
        r.pos.y>=pos.y &&
        r.pos.y+r.size.y<=pos.y+size.y);
}
bool overlaps(const rect& r) const{
return (pos.x < r.pos.x + r.size.x && pos.x+size.x>=r.pos.x && pos.y <r.pos.y+r.size.y && pos.y+size.y>=r.pos.y);
}
};



template<typename T>
struct QuadTreeItemLocation{
typename std::list<std::pair<rect,T>>* container;
typename std::list<std::pair<rect,T>>::iterator iterator;
};

template <typename OBJECT_TYPE>
class DynamicQuadTree{
    size_t MAX_DEPTH=8;
public:

DynamicQuadTree(const rect& size ={{0.0f,0.0f},{100.f,100.f}}, const size_t nDepth = 0){
m_depth=nDepth;
resize(size);
}

void resize(const rect& rArea){
clear();
m_rect=rArea;

//potomkowie maj¹ po³owe d³ugoœci ojca
//kwadrat dzieli sie na 4 mniejsze
sf::Vector2f vChildSize=m_rect.size / 2.0f;
m_rChild={
rect(m_rect.pos, vChildSize), //1
rect({m_rect.pos.x+vChildSize.x,m_rect.pos.y},vChildSize), //2
rect({m_rect.pos.x,m_rect.pos.y+vChildSize.y},vChildSize), //3
rect({m_rect.pos.x+vChildSize.x,m_rect.pos.y+vChildSize.y}, vChildSize) //4
};
}

// funkcja clear czysci drzewo
void clear(){
	m_pItems.clear();
	for(int i=0; i<4; i++){
		if(m_pChild[i])	m_pChild[i]->clear();
		m_pChild[i].reset();
	}
}

size_t size() const{
	size_t nCount = m_pItems.size();
	for(int i=0; i<4; i++){
	if(m_pChild[i]) nCount+=m_pChild[i]->size();
	}
	return nCount;
}

QuadTreeItemLocation<OBJECT_TYPE> insert(const OBJECT_TYPE& item, const rect& itemSize){
for(int i=0; i<4; i++){
	//czy obiekt znajduje siê w potomku?
	if(m_rChild[i].contains(itemSize)){
		//czy dotarliœmy do maksymalnej g³êbokoœci
		if(m_depth + 1 < MAX_DEPTH){
			//jeœli nie, to czy istnieje potomek?
			if(!m_pChild[i]){

			//nie, wiêc trzeba go stworzyæ
			m_pChild[i]=std::make_shared<DynamicQuadTree<OBJECT_TYPE>>(m_rChild[i],m_depth);
			}
			//teraz napewno istnieje potomek, bo zosta³ utworzony
			//mo¿na wiec do niego coœ dodaæ
			return m_pChild[i]->insert(item,itemSize);

		}
	}
}
	//nie zmiescil sie, wiec musi byc w aktualnej warstwie
	m_pItems.push_back({itemSize,item});
	return {&m_pItems,std::prev(m_pItems.end())};
}

	//zwraca obiekty w danym obszarze
std::list<OBJECT_TYPE> search(const rect& rArea) const{
	std::list<OBJECT_TYPE> listItems;
	search(rArea,listItems);
	return listItems;
}
void search(const rect& rArea, std::list<OBJECT_TYPE>& listItems) const{
//najpierw sprawdzamy obiekty, ktore naleza do listy
for(const auto& p : m_pItems){
	if(rArea.overlaps(p.first))
		listItems.push_back(p.second);
	}
	//potem rekurencyjnie sprawdz czy potomkowie naleza do listy
	for(int i=0; i<4; i++){
		if(m_pChild[i]){
			if(rArea.contains(m_rChild[i])) m_pChild[i]->items(listItems);

			else if(m_rChild[i].overlaps(rArea)) m_pChild[i]->search(rArea, listItems);
		}

	}
}

void items(std::list<OBJECT_TYPE>& listItems) const{
	for(const auto& p : m_pItems){
		listItems.push_back(p.second);
	}
	for(int i=0; i<4; i++){
		if(m_pChild[i]) m_pChild[i]->items(listItems);
	}
}
const rect& area(){
return m_rect;
}


protected:

//glebokosc drzewa
std::size_t m_depth = 0;

//pole drzewa czwórkowego
rect m_rect;

//cztery pola potomków drzewa
std::array<rect, 4> m_rChild{};

//potencjalni 4 potomkowie drzewa
std::array<std::shared_ptr<DynamicQuadTree<OBJECT_TYPE>>,4> m_pChild{};

//objekty aktualnie w tym drzewie
std::list<std::pair<rect, OBJECT_TYPE>> m_pItems;
};


template<typename T>
struct QuadTreeItem{
T item;
QuadTreeItemLocation<typename std::list<QuadTreeItem<T>>::iterator> pItem;
};

template<typename OBJECT_TYPE>
class DynamicQuadTreeContainer{
	using QuadTreeContainer = std::list<QuadTreeItem<OBJECT_TYPE>>;

	protected:
	QuadTreeContainer m_allItems;
	DynamicQuadTree<typename QuadTreeContainer::iterator> root;

	public:

	DynamicQuadTreeContainer(const rect& size={{0.f,0.f},{100.f,100.f}}, const size_t nDepth=0) : root(size){

	}

	void resize(const rect& rArea){
	root.resize(rArea);
	}
	size_t size() const{
	return m_allItems.size();
	}
	bool empty() const{
		return m_allItems.empty();
	}

	void clear(){
	root.clear();
	m_allItems.clear();
	}
	typename QuadTreeContainer::iterator begin(){
		return m_allItems.begin();
	}
	typename QuadTreeContainer::iterator end(){
		return m_allItems.end();
	}
	typename QuadTreeContainer::iterator cbegin(){
		return m_allItems.cbegin();
	}
	typename QuadTreeContainer::iterator cend(){
		return m_allItems.cend();
	}
	void insert(const OBJECT_TYPE& item, const rect& itemSize){

	    QuadTreeItem<OBJECT_TYPE> newItem;
	    newItem.item=item;


		m_allItems.push_back(newItem);
		m_allItems.back().pItem=root.insert(std::prev(m_allItems.end()),itemSize);
	}
	std::list<typename QuadTreeContainer::iterator> search(const rect& rArea){

		std::list<typename QuadTreeContainer::iterator> listItemPointers;
		root.search(rArea,listItemPointers);
		return listItemPointers;
	}
	const std::list<typename QuadTreeContainer::iterator> searchConst(const rect& rArea) const{
        std::list<typename QuadTreeContainer::iterator> listItemPointers;
		root.search(rArea,listItemPointers);
		return listItemPointers;
	}
	void remove(typename QuadTreeContainer::iterator item){

	    item->pItem.container->erase(item->pItem.iterator);

	m_allItems.erase(item);
	}

	void relocate(typename QuadTreeContainer::iterator& item, const rect& itemsize){

	item->pItem.container->erase(item->pItem.iterator);

	item->pItem=root.insert(item,itemsize);
	}
};

#endif // QUADTREE_H

