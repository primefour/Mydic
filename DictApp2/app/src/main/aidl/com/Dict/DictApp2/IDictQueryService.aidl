package com.Dict.DictApp2;

import java.util.List;

interface IDictQueryService{
String queryWord(String word);
boolean addDictionary(String name);
boolean removeDictionary(String name);
void scanPath(String path);
List<String> getDictList();
}
