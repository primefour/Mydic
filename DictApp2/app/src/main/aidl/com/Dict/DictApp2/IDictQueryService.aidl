package com.Dict.DictApp2;

import java.util.List;
import java.util.Map;

interface IDictQueryService{
String queryWord(String word);
boolean addDictionary(String name);
boolean removeDictionary(String name);
void scanPath(String path);
List<String> getDictList();
boolean getDictStatus(String name);
void setDictStatus(String name,boolean flag);
}
