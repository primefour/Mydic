package com.primefour.robot;

import java.util.ArrayList;
import java.util.Iterator;

public class HtmlInputForm {
	private String mMothed;
	private String mBaseUrl;
	private ArrayList<HtmlSelectOption> mSelectList;
	private ArrayList<HtmlUserInput> mInputList;
	
	public HtmlInputForm(String baseUrl,String mothed){
		mMothed = mothed;
		mBaseUrl = baseUrl;
		mSelectList = new ArrayList<HtmlSelectOption>();
		mInputList = new ArrayList<HtmlUserInput>();
	}
	
	public void AddSelectItem(HtmlSelectOption se){
		mSelectList.add(se);
	}
	
	public void AddInputItem(HtmlUserInput ui) {
		mInputList.add(ui);
	}
	
	public String getParameterString(){
		StringBuilder sb = new StringBuilder();
		Iterator<HtmlSelectOption> ih =  mSelectList.iterator();
		while(ih.hasNext()){
			HtmlSelectOption ho = ih.next();
			sb.append(ho.getCommitString());
			sb.append("&");
		}
		
		Iterator<HtmlUserInput> iui =  mInputList.iterator();
		while(iui.hasNext()){
			HtmlUserInput ui = iui.next();
			sb.append(ui.getCommitString());
			sb.append("&");
		}
		return sb.toString();
	}
	public String getBaseUri(){
		return mBaseUrl;
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder();
		Iterator<HtmlSelectOption> ih =  mSelectList.iterator();
		sb.append("#####################Input Form##########################\n");
		while(ih.hasNext()){
			HtmlSelectOption ho = ih.next();
			sb.append(ho.toString());
			sb.append("\n");
		}
		Iterator<HtmlUserInput> iui =  mInputList.iterator();
		while(iui.hasNext()){
			HtmlUserInput ui = iui.next();
			sb.append(ui.toString());
			sb.append("\n");
		}
		sb.append("###############################################\n");
		return sb.toString();
	}
}
