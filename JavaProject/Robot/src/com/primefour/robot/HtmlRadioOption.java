package com.primefour.robot;

import java.util.Collection;
import java.util.Iterator;

public class HtmlRadioOption extends HtmlSelectOption {
	HtmlRadioOption(String title,String name,String id){
		super(title,name,id);
	}
	
	public void SetItemEnable(String key){
		Collection<String> keySet = mOptionList.keySet();
		Iterator<String> it = keySet.iterator(); 
		for(;it.hasNext();){
			String kkey = it.next();
			ItemValue iv = mOptionList.get(kkey);
			iv.mSelected = "false";
			mOptionList.put(key,iv);
		}
		
		if(mOptionList.containsKey(key)){
			ItemValue vi =  mOptionList.get(key);
			vi.mSelected = "true";
			mOptionList.put(key,vi);
		}
	}
	
	//generate commit string
	public String getCommitString(){
		Collection<String> keySet = mOptionList.keySet();
		Iterator<String> it = keySet.iterator(); 
		for(;it.hasNext();){
			String key = it.next();
			ItemValue iv = mOptionList.get(key);
			if("true".equals(iv.mSelected.toLowerCase())){
				return mName + "=" + iv.mValue;
			}
		}
		return null;
	}
}
