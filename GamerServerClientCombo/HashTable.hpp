//
//  HashTable.hpp
//  GamerServerClientCombo
//
//  Created by Thomas Redding on 12/3/15.
//  Copyright © 2015 Thomas Redding. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include <vector>

/*
 * HashTable that works with any object with a public instance variable called "id" of type int, long, etc.
 */

template <class V>
class HashTable {
private:
	int entriesNum = 0;
	std::vector<std::vector<V*>> table;
	std::vector<V> entries;
	void expand() {
		//
	}
public:
	HashTable() {
		table = std::vector<std::vector<V*>>(10);
	}
	void set(int key, V value) {
		int index = key%table.size();
		for(int i=0; i<table[index].size(); i++) {
			if(table[index][i].id == key) {
				table[index][i]->value = value;
				return;
			}
		}
		entries.push_back(value);
		table[index].push_back(&entries[entries.size()-1]);
		entriesNum++;
		if(1.0*entriesNum/table.size() > 1)
			expand();
	}
	V* get(int key) {
		int index = key%table.size();
		for(int i=0; i<table[index].size(); i++) {
			if(table[index][i]->key == key) {
				return &table[index][i]->value;
			}
		}
		return nullptr;
	}
	const std::vector<V>& getList() { return entries; }
};

#endif /* HashTable_hpp */
