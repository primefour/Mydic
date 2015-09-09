package com.primefour.robot;

import java.net.InetAddress;
import java.util.ArrayList;

public class HTMLParser {
	
	ArrayList<String> mHrefList;
	ArrayList<HtmlSelectOption> mSelectList;
	
	
	public HTMLParser(String path){
		
	}
	public HTMLParser(byte data,int length){
		
	}
	public HTMLParser(InetAddress servAddr){
		
	}
	
	
	

	public ArrayList<String> extractNoCase(String str,String token1,String token2,int count) {
		
		String str1 = str.toLowerCase();
		String tok1 = token1.toLowerCase();
		String tok2 = token2.toLowerCase();
		
		ArrayList<String> list = new ArrayList<String>();
		int toffset1 = 0;
		int toffset2 = 0;
		while(count > 0) {
			toffset1 = str1.indexOf(tok1,toffset1);
			if(toffset1 == -1){
				return list;
			}
			toffset2 = str1.indexOf(tok2, toffset1);
			if(toffset2 == -1){
				return list;
			}
			list.add(str1.substring(toffset1 + tok1.length(), toffset2));
			toffset1 = toffset2 ;
			count --;
		}
		return list;
	}
}
