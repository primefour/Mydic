package com.primefour.robot;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class HtmlSelectOption {
	protected String mTitle;
	protected String mName;
	protected String mId; 
	protected class ItemValue{
		public String mValue;
		public String mSelected;
		public ItemValue(String value,String sel){
			mValue = value;
			mSelected = sel;
		}
	};
	protected Map<String,ItemValue> mOptionList;
	
	public ItemValue getItemValue(String value,String sel){
		return new ItemValue(value,sel);
	}
	
	public HtmlSelectOption(String title,String name,String id){
		mTitle = title;
		mName = name;
		mId = id;
		mOptionList = new HashMap<String,ItemValue>();
	}
	
	public void HtmlAddSelectItem(String ItemName,ItemValue value){
		//update as new values
		if(mOptionList.containsKey(ItemName)){
			mOptionList.remove(ItemName);
		}
		mOptionList.put(ItemName,value);
	}
	
	public ArrayList<String> getEnableItems(){
		Collection<String> keySet = mOptionList.keySet();
		Iterator<String> it = keySet.iterator(); 
		ArrayList<String> list = new ArrayList<String>();
		for(;it.hasNext();){
			String key = it.next();
			list.add(key);
		}
		return list; 
	}
	
	public String getEnableItem(){
		Collection<String> keySet = mOptionList.keySet();
		Iterator<String> it = keySet.iterator(); 
		for(;it.hasNext();){
			String key = it.next();
			return key;
		}
		return null;
	}
	
	public String getName(){
		return mName;
	}
	
	//generate commit string
	public String getCommitString(){
		return null;
	}
	
	public String getTitle(){
		return mTitle;
	}
	
	public String getId(){
		return mId;
	}
}
