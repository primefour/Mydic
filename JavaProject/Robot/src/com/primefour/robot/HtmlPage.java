package com.primefour.robot;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

public class HtmlPage {
	private URL mURL;
	private InputStream mIS;
	private String mTextContent;
	private String mScriptContent;
	private String mStyleContent;
	
	private ArrayList<HtmlFormRequest> mInputList = new ArrayList<HtmlFormRequest>();
	private HashMap<String,HtmlHRef> mHRef = new HashMap<String,HtmlHRef>();
	
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
		//StringBuilder result = new StringBuilder();
		StringBuilder fullText = new StringBuilder();
		StringBuilder fullScript = new StringBuilder();
		StringBuilder fullStyle = new StringBuilder();
		HTMLTag ht = null;
		boolean formBegin = false;
		boolean hasSelect = false;
		HtmlFormRequest formInst = null;
		HtmlRadioOption radioOpt = null;
		HtmlCheckOption checkOpt = null;
		HtmlRadioOption singleSelOpt = null;
		HtmlCheckOption multSelOpt = null;
		
		byte textBuff[] = new byte[409600];
		int idx = 0;
		while ((ch = parse.read()) != -1) {
			if (ch == 0) {
				//if(ht != null && result.length() != 0){
				if(ht != null && idx != 0){
					byte data[] = new byte[idx];
					System.arraycopy(textBuff,0,data,0,idx);
					String result = new String(data,"utf8");
					if(ht.getName().equalsIgnoreCase("script")){
						fullScript.append(result);
					}else if(ht.getName().equalsIgnoreCase("style")){
						fullStyle.append(result);
					}else{
						fullText.append(result);
					}
					ht.setContent(result);
					idx = 0;
				}
				if(ht != null){
					if(formBegin){
						String tagName = ht.getName();
						if(tagName.equalsIgnoreCase("/form")){	
							System.out.println("end ##form" + ht.getName());
							formBegin = false ;
							if(radioOpt != null){
								formInst.insertSelectInput(radioOpt);
								radioOpt  = null;
							}
							if(checkOpt != null){
								formInst.insertSelectInput(checkOpt);
								checkOpt = null;
							}
							System.out.println("xxxxxxxxxx form request " + formInst.getBaseUri());
							mInputList.add(formInst);
							formInst = null;
						}else if(tagName.equalsIgnoreCase("input")){
							String tagType = ht.getAttributeValue("type");
							if(tagType == null || tagType.equalsIgnoreCase("password") ||
									tagType.equalsIgnoreCase("text")){								
								System.out.println("new ##text input " + ht.getName());
								formInst.insertUserInput(new HtmlUserInput(ht));
							}else if(tagType.equalsIgnoreCase("radio")){
								System.out.println("new ##radio input " + ht.getName());
								if(radioOpt == null){
									radioOpt = new HtmlRadioOption(ht.getAttributeValue("name"));
									radioOpt.addSelectItem(ht);
								}else{
									radioOpt.addSelectItem(ht);
								}
							}else if(tagType.equalsIgnoreCase("checkbox")){
								System.out.println("new ##checkbox input " + ht.getName());
								if(checkOpt == null){
									checkOpt = new HtmlCheckOption(ht.getAttributeValue("name"));
									checkOpt.addSelectItem(ht);
								}else{
									checkOpt.addSelectItem(ht);
								}
							}else if(tagType.equalsIgnoreCase("file")){
								
							}else if(tagType.equalsIgnoreCase("submit") || 
										tagType.equalsIgnoreCase("image")){
								
							}
						}else if(tagName.equalsIgnoreCase("textarea")){
							System.out.println("new ##textarea input " + ht.getName());
							formInst.insertUserInput(new HtmlUserInput(ht));
						}else if(tagName.equalsIgnoreCase("select")){
							System.out.println("new ##select input " + ht.getName());
							if(ht.getAttributeValue("multiple") != null && ht.getAttributeValue("multiple").equalsIgnoreCase("multiple")){
								multSelOpt 	= new HtmlCheckOption(ht.getAttributeValue("name"));
							}else{
								singleSelOpt = new HtmlRadioOption(ht.getAttributeValue("name"));
							}
							hasSelect = true;
						}else if(tagName.equalsIgnoreCase("option") && hasSelect){
							System.out.println("get ##select option" + ht.getName());
							if(singleSelOpt != null ){
								singleSelOpt.addSelectItem(ht);
							}else{
								multSelOpt.addSelectItem(ht);
							}
						}else if(tagName.equalsIgnoreCase("/select") && hasSelect){
							System.out.println("end ##select input " + ht.getName());
							hasSelect = false;
							if(singleSelOpt != null ){
								formInst.insertSelectInput(singleSelOpt);
								singleSelOpt = null;
							}else{
								formInst.insertSelectInput(multSelOpt);
								multSelOpt = null;
							}
						}
					}else if(ht.getName().equalsIgnoreCase("a")){
						System.out.println("new ##link" + ht.getAttributeValue("href"));
						if(ht.getAttributeValue("href") == null){
							
						} else if(ht.getAttributeValue("href").indexOf("http") != -1){
							mHRef.put(ht.getAttributeValue("href"),new HtmlHRef(ht));
						}else if(ht.getAttributeValue("href").indexOf("mailto") != -1){
							System.out.println("new ##mail to" + ht.getAttributeValue("href"));
							System.out.println("new ##mail to" + ht.getAttributeValue("href").substring(
										ht.getAttributeValue("href").indexOf(":") + ":".length(),ht.getAttributeValue("href").length()));
						}else{
							if(mURL == null){
								mHRef.put(null,new HtmlHRef(null,ht));
							}else{
								mHRef.put("http://" + mURL.getHost() + "/",new HtmlHRef("http://" + mURL.getHost() + "/",ht));
							}
						}
					}else if(ht.getName().equalsIgnoreCase("form")){
						formBegin = true;
						formInst = new HtmlFormRequest(ht);
						System.out.println("new ##form" + ht.getName());
					}
				}
				ht = (HTMLTag) parse.getTag().clone();
			}else if(ch != -1){
				textBuff[idx ++] = (byte)ch ;
			}
		}
		mTextContent = fullText.toString();
		mScriptContent = fullScript.toString();
		mStyleContent = fullStyle.toString();
	}
	
	private void parserAllElements() throws IOException{
			HTMLParser parser = new HTMLParser(mIS);
			doAction(parser);
	}
	
	public void writeHref(OutputStream op) throws IOException{
		StringBuilder sb = new StringBuilder();
		Set<String> it = mHRef.keySet();
		for(String em :it){
			HtmlHRef item = mHRef.get(em);
			op.write(item.toString().getBytes());
		}
	}
	
	public String getContent(){
		return mTextContent;
	}
	
	public void writeInput(OutputStream op) throws IOException{
		StringBuilder sb = new StringBuilder();
		Iterator<HtmlFormRequest> ii = mInputList.iterator(); 
		for(;ii.hasNext();){
			HtmlFormRequest item = ii.next();	
			sb.append(item.getHtmlReqStr());
			sb.append("\n");
		}
		op.write(sb.toString().getBytes());
	}
	
	public String toString(){
		StringBuilder sb = new StringBuilder();
		Set<String> it = mHRef.keySet();
		sb.append("######link list is :\n");
		for(String em :it){
			HtmlHRef item = mHRef.get(em);
			System.out.println(item);
			sb.append(item.getBaseUrl());
			sb.append("\n");
		}
		
		sb.append("######input list is :\n");
		
		Iterator<HtmlFormRequest> ii = mInputList.iterator(); 
		for(;ii.hasNext();){
			HtmlFormRequest item = ii.next();	
			System.out.println(item.getHtmlReqStr());
			sb.append(item.getHtmlReqStr());
			sb.append("\n");
		}
		
		sb.append("full text :\n");
		sb.append(mTextContent);
		
		sb.append("full script :\n");
		sb.append(mScriptContent);
		
		sb.append("full style :\n");
		sb.append(mStyleContent);
		return sb.toString(); 
	}
	
}
