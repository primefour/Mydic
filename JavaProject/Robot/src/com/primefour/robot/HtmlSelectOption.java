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
		public String mValueName;
		public String mSelected;
		public ItemValue(String name,String sel){
			mValueName = name;
			mSelected = sel;
		}
		public ItemValue(HTMLTag tag){
			mValueName = tag.getAttributeValue("value");
			mSelected = "false";
		}
	};
	
	protected ArrayList<ItemValue> mOptionList;
	
	public ItemValue getItemValue(String Name,String sel){
		return new ItemValue(Name,sel);
	}
	
	public ItemValue getItemValue(HTMLTag tag){
		return new ItemValue(tag);
	}
	
	public HtmlSelectOption(String title,String name,String id){
		mTitle = title;
		mName = name;
		mId = id;
		mOptionList = new ArrayList<ItemValue>();
	}
	
	public void SetItemEnable(String key){
		Iterator<ItemValue> it = mOptionList.iterator(); 
		for(;it.hasNext();){
			ItemValue item = it.next();
			if(item.mValueName.equalsIgnoreCase(key)){
				item.mSelected = "true";
			}
		}
	}
	
	public void addSelectItem(ItemValue item){
		//update as new values
		mOptionList.add(item);
	}
	
	public void addSelectItem(HTMLTag tag){
		//update as new values
		mOptionList.add(new ItemValue(tag));
	}
	
	public String getName(){
		return mName;
	}
	
	public void setName(String name){
		mName = name;
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
