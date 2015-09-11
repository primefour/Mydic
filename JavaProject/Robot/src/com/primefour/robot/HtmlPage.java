package com.primefour.robot;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.Iterator;

public class HtmlPage {
	private URL mURL;
	private InputStream mIS;
	
	private ArrayList<HtmlFormRequest> mInputList = new ArrayList<HtmlFormRequest>();
	private ArrayList<HtmlHRef> mHRef = new ArrayList<HtmlHRef>();
	
	public HtmlPage(String url) throws MalformedURLException{
		mURL = new URL(url);
		try {
			HttpURLConnection conn = (HttpURLConnection) mURL.openConnection();
			conn.setReadTimeout(1000);
			conn.setConnectTimeout(1000);
			mIS = conn.getInputStream();
			parserAllElements();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public HtmlPage(InputStream in){
		mIS = in;
		try {
			parserAllElements();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void doAction(HTMLParser parse) throws IOException {
		int ch;
		StringBuilder result = new StringBuilder();
		HTMLTag ht = null;
		boolean formBegin = false;
		boolean hasSelect = false;
		HtmlFormRequest formInst = null;
		HtmlRadioOption radioOpt = null;
		HtmlCheckOption checkOpt = null;
		HtmlRadioOption singleSelOpt = null;
		HtmlCheckOption multSelOpt = null;
		while ((ch = parse.read()) != -1) {
			if (ch == 0) {
				if(ht != null && result.length() != 0){
					ht.setContent(result.toString());
					result.setLength(0);
				}
				if(ht != null){
					System.out.println("##" + ht);
					if(formBegin){
						String tagName = ht.getName();
						if(tagName.equalsIgnoreCase("/form")){	
							formBegin = false ;
							if(radioOpt != null){
								formInst.insertSelectInput(radioOpt);
								radioOpt  = null;
							}
							if(checkOpt != null){
								formInst.insertSelectInput(checkOpt);
								checkOpt = null;
							}
							mInputList.add(formInst);
							formInst = null;
						}else if(tagName.equalsIgnoreCase("input")){
							String tagType = ht.getAttributeValue("type");
							if(tagType.equalsIgnoreCase("password") ||
									tagType.equalsIgnoreCase("text") ||
									tagType.equalsIgnoreCase("submit") ||
									tagType.equalsIgnoreCase("image")){								
								formInst.insertUserInput(new HtmlUserInput(ht));
							}else if(tagType.equalsIgnoreCase("radio")){
								if(radioOpt == null){
									radioOpt = new HtmlRadioOption(ht.getAttributeValue("name"));
									radioOpt.addSelectItem(ht);
								}else{
									radioOpt.addSelectItem(ht);
								}
							}else if(tagType.equalsIgnoreCase("checkbox")){
								if(checkOpt == null){
									checkOpt = new HtmlCheckOption(ht.getAttributeValue("name"));
									checkOpt.addSelectItem(ht);
								}else{
									checkOpt.addSelectItem(ht);
								}
							}
						}else if(tagName.equalsIgnoreCase("textarea")){
							formInst.insertUserInput(new HtmlUserInput(ht));
						}else if(tagName.equalsIgnoreCase("select")){
							if(ht.getAttributeValue("multiple").equalsIgnoreCase("multiple")){
								multSelOpt 	= new HtmlCheckOption(ht.getAttributeValue("name"));
							}else{
								singleSelOpt = new HtmlRadioOption(ht.getAttributeValue("name"));
							}
							hasSelect = true;
						}else if(tagName.equalsIgnoreCase("option") && hasSelect){
							if(singleSelOpt != null ){
								singleSelOpt.addSelectItem(ht);
							}else{
								multSelOpt.addSelectItem(ht);
							}
						}else if(tagName.equalsIgnoreCase("/select") && hasSelect){
							hasSelect = false;
							if(singleSelOpt != null ){
								formInst.insertSelectInput(singleSelOpt);
							}else{
								formInst.insertSelectInput(multSelOpt);
							}
						}
					}else{
						if(ht.getName().equalsIgnoreCase("a")){
							if(ht.getAttributeValue("href").indexOf("http") != -1){
								mHRef.add(new HtmlHRef(ht));
							}else{
								mHRef.add(new HtmlHRef(mURL.toString(),ht));
							}
						}else if(ht.getName().equalsIgnoreCase("form")){
							formBegin = true;
							formInst = new HtmlFormRequest(ht);
						}
					}
				}
				ht = (HTMLTag) parse.getTag().clone();
			}else if(ch != -1){
				result.append((char)ch);
			}
		}
	}
	
	private void parserAllElements() throws IOException{
			HTMLParser parser = new HTMLParser(mIS);
			doAction(parser);
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder();
		Iterator<HtmlHRef> it = mHRef.iterator(); 
		sb.append("link list is :\n");
		for(;it.hasNext();){
			HtmlHRef item = it.next();	
			System.out.println(item.getBaseUrl());
			sb.append(item.getBaseUrl());
			sb.append("\n");
		}
		
		sb.append("input list is :\n");
		
		Iterator<HtmlFormRequest> ii = mInputList.iterator(); 
		for(;it.hasNext();){
			HtmlFormRequest item = ii.next();	
			System.out.println(item.getHtmlReqStr());
			sb.append(item.getHtmlReqStr());
			sb.append("\n");
		}
		
		return sb.toString(); 
	}
	
	
	
	
	
	
	
	
	
	
}
