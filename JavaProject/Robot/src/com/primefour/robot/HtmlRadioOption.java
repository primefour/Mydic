package com.primefour.robot;

import java.util.Collection;
import java.util.Iterator;

public class HtmlRadioOption extends HtmlSelectOption {
	
	public HtmlRadioOption(String title,String name,String id){
		super(title,name,id);
	}
	
	public HtmlRadioOption(String name){
		super(null,name,null);
	}
	
	
	public void SetItemEnable(String key){
		Iterator<ItemValue> it = mOptionList.iterator(); 
		for(;it.hasNext();){
			ItemValue item = it.next();
			item.mSelected = "false";
			if(item.mValueName.equalsIgnoreCase(key)){
				item.mSelected = "true";
			}
		}
	}
	
	//generate commit string
	public String getCommitString(){
		Iterator<ItemValue> it = mOptionList.iterator(); 
		for(;it.hasNext();){
			ItemValue item = it.next();
			if("true".equals(item.mSelected.toLowerCase())){
				return mName + "=" + item.mValueName;
			}
		}
		return null;
	}
}
