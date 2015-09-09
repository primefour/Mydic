package com.primefour.robot;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class HtmlSelectOption {
	private String mBaseUrl ;
	private String mTitle;
	private String mId; 
	private Map<String,Boolean> mOptionList;
	
	public HtmlSelectOption(String baseUrl,String title,String id){
		mTitle = title;
		mId = id;
		mBaseUrl = baseUrl;
		mOptionList = new HashMap<String,Boolean>();
	}
	
	public void HtmlAddSelectItem(String ItemName,boolean selected){
		//update as new values
		if(mOptionList.containsKey(ItemName)){
			mOptionList.remove(ItemName);
		}
		mOptionList.put(ItemName,selected);
	}
	
	public ArrayList<String> getEnableItems(){
		Collection<String> keySet = mOptionList.keySet();
		Iterator<String> it = keySet.iterator(); 
		ArrayList<String> list = new ArrayList<String>();
		for(;it.hasNext();){
			String key = it.next();
			if(mOptionList.get(key)){
				list.add(key);
			}
		}
		return list; 
	}
	
	public String getEnableItem(){
		Collection<String> keySet = mOptionList.keySet();
		Iterator<String> it = keySet.iterator(); 
		for(;it.hasNext();){
			String key = it.next();
			if(mOptionList.get(key)){
				return key;
			}
		}
		return null; 
	}
	
	public String getBaseUrl(){
		return mBaseUrl;
	}
	
	public String getTitle(){
		return mTitle;
	}
	
	public String getId(){
		return mId;
	}
}
