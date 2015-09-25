package com.primefour.robot;

import java.util.ArrayList;
import java.util.Iterator;

public class HtmlFormRequest {
	private String mBaseUri;
	private String mReqMethod;
	private String mName;
	private String mId ;
	private ArrayList<HtmlSelectOption> mSelectOptionList;
	private ArrayList<HtmlUserInput> mUserInputList;
	
	public HtmlFormRequest(String uri,String method,String name,String id){
		mName = name;
		mId = id;
		mReqMethod = method;
		if(mReqMethod == null){
			mReqMethod = "get" ;
		}
		mBaseUri = uri;
		mSelectOptionList = new ArrayList<HtmlSelectOption>();
		mUserInputList = new ArrayList<HtmlUserInput>();
	}
	
	public HtmlFormRequest(HTMLTag tag){
		mName = tag.getAttributeValue("name");
		mId = tag.getAttributeValue("id");
		mReqMethod = tag.getAttributeValue("method");
		mBaseUri = tag.getAttributeValue("action");
		mSelectOptionList = new ArrayList<HtmlSelectOption>();
		mUserInputList = new ArrayList<HtmlUserInput>();
		//System.out.println(mName);
	}
	
	
	public void insertSelectInput(HtmlSelectOption so){
		mSelectOptionList.add(so);
//		System.out.println("####select " + so.getName());
	}
	
	public void insertUserInput(HtmlUserInput si){
		mUserInputList.add(si);
//		System.out.println("Input ####"+si.getInputName());
	}
	
	public String getBaseUri(){
		return mBaseUri;
	}
	
	public HtmlSelectOption getSelectByName(String name){
			Iterator<HtmlSelectOption> hi = mSelectOptionList.iterator();
			while(hi.hasNext()){
				HtmlSelectOption hso = hi.next();
				if(hso.getName().equalsIgnoreCase(name)){
					return hso;
				}
			}
			return null;
	}
	
	public HtmlUserInput getInputByName(String name){
			Iterator<HtmlUserInput> hu = mUserInputList.iterator();
			while(hu.hasNext()){
				HtmlUserInput hui = hu.next();
				if(hui.getInputName().equalsIgnoreCase(name)){
					return hui;
				}
			}
			return null;
	}
	
	public String getHtmlReqStr(){
		StringBuilder sb = new StringBuilder();
		if((mReqMethod == null) || ("get".equals(mReqMethod.toLowerCase()))){
			sb.append(mBaseUri);
			sb.append("?");
			Iterator<HtmlSelectOption> hi = mSelectOptionList.iterator();
			while(hi.hasNext()){
				HtmlSelectOption hso = hi.next();
				sb.append(hso.getCommitString());
				sb.append('&');
			}
			
			Iterator<HtmlUserInput> hu = mUserInputList.iterator();
			while(hu.hasNext()){
				HtmlUserInput hui = hu.next();
				sb.append(hui.getCommitString());
				sb.append('&');
			}
			if(sb.length() != 0){
				sb.setLength(sb.length() -1);
			}
			return sb.toString();
		}else{
			Iterator<HtmlSelectOption> hi = mSelectOptionList.iterator();
			while(hi.hasNext()){
				HtmlSelectOption hso = hi.next();
				sb.append(hso.getCommitString());
				sb.append('&');
			}
			
			Iterator<HtmlUserInput> hu = mUserInputList.iterator();
			while(hu.hasNext()){
				HtmlUserInput hui = hu.next();
				sb.append(hui.getCommitString());
				sb.append('&');
			}
			if(sb.length() != 0){
				sb.setLength(sb.length() -1);
			}
			return sb.toString();
		}
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder();
		Iterator<HtmlSelectOption> ih =  mSelectOptionList.iterator();
		sb.append("#####################Input Form##########################\n");
		while(ih.hasNext()){
			HtmlSelectOption ho = ih.next();
			sb.append(ho.toString());
			sb.append("\n");
		}
		Iterator<HtmlUserInput> iui =  mUserInputList.iterator();
		while(iui.hasNext()){
			HtmlUserInput ui = iui.next();
			sb.append(ui.toString());
			sb.append("\n");
		}
		sb.append("###############################################\n");
		return sb.toString();
	}
}
