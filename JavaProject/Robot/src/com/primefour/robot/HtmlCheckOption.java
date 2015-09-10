package com.primefour.robot;

import java.util.Collection;
import java.util.Iterator;

public class HtmlCheckOption extends HtmlSelectOption {
	
	public  HtmlCheckOption(String title,String name,String id){
		super(title,name,id);
	}
	
	public void SetItemEnable(String key){
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
		StringBuilder sb = new StringBuilder();
		for(;it.hasNext();){
			String key = it.next();
			ItemValue iv = mOptionList.get(key);
			if("true".equals(iv.mSelected.toLowerCase())){
				sb.append(mName);
				sb.append("=");
				sb.append(iv.mValue);
				sb.append("&");
			}
		}
		sb.setCharAt(sb.length(),'\0');
		return sb.toString();
	}
}
