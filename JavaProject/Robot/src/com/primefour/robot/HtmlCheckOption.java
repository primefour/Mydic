package com.primefour.robot;

import java.util.Collection;
import java.util.Iterator;

public class HtmlCheckOption extends HtmlSelectOption {
	
	public  HtmlCheckOption(String title,String name,String id){
		super(title,name,id);
	}
	
	public  HtmlCheckOption(String name){
		super(null,name,null);
	}
	//generate commit string
	public String getCommitString(){
		Iterator<ItemValue> it = mOptionList.iterator(); 
		StringBuilder sb = new StringBuilder();
		if(!mOptionList.isEmpty()){
			mOptionList.get(0).mSelected = "true";
		}else{
			return null;
		}
		for(;it.hasNext();){
			ItemValue item = it.next();
			if("true".equals(item.mSelected.toLowerCase())){
				sb.append(mName);
				sb.append("=");
				sb.append(item.mValueName);
				sb.append("&");
			}
		}
		if(sb.length() != 0){
			sb.setLength(sb.length() -1);
		}
		return sb.toString();
	}
	
}
