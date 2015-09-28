package com.primefour.robot;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.zip.GZIPInputStream;

public class AmazonJPOrder {
	private static final String mUrl = "http://www.amazon.jp";
	private HtmlPage  mHtmlPage;
	private CookieUtility mCookieManager = new CookieUtility();
	private String mUserName;
	private String mPassWord;
	
	void connectHttp(String url,String fileName){
		System.out.println(url);
		URL turl = null;
		try {
			turl = new URL(url);
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		HttpURLConnection conn;
		try {
			conn = (HttpURLConnection) turl.openConnection();
			mCookieManager.saveCookies(conn);
			conn.setRequestProperty("User-Agent","Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:38.0) Gecko/20100101 Firefox/38.0");
			conn.setRequestProperty("Connection","keep-alive");
			conn.setRequestProperty("Accept","text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
			conn.setRequestProperty("Accept-Language","zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3");
			conn.setRequestProperty("Accept-Encoding","gzip, deflate");
			conn.setInstanceFollowRedirects(false);
			InputStream is = conn.getInputStream();
			if(conn.getContentEncoding() != null && conn.getContentEncoding().equalsIgnoreCase("gzip")){
				is = new GZIPInputStream(is);
			}
			FileOutputStream fo = new FileOutputStream(fileName + ".html");
			byte buff[] = new byte[1024];
			int ret = 0 ;
			while((ret = is.read(buff)) != -1){
				fo.write(buff,0,ret);
			}
			fo.close();
			
			FileInputStream fi = new FileInputStream(fileName + ".html");
			//BufferedReader reader = new BufferedReader(new InputStreamReader(is,"utf8"));  
			/*
			BufferedReader reader = new BufferedReader(new InputStreamReader(gis,"utf8"));  
			String line = null;
			while( (line = reader.readLine()) != null){
				System.out.println(line);
			}
			*/
			
			int code = conn.getResponseCode();
			mCookieManager.loadCookies(conn);
			System.out.println("Code  = " + code);
			if(code < 400 && code >= 300){
				//relocation
				System.out.println(conn.getHeaderField("location"));
				connectHttp(conn.getHeaderField("location"),fileName);
			}else if(code < 300){
				mHtmlPage = new HtmlPage(fi,mUrl);
				String content = mHtmlPage.toString();
				FileOutputStream fos = new FileOutputStream(fileName);
				fos.write(content.getBytes());
			}
			is.close();
			fi.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}finally{
		}
		
	}
	
	boolean searchProduct(String name){
		mHtmlPage.setRequestValue("field-keywords",name);
		String searchUrl = mUrl + mHtmlPage.getRequstString(null);
		System.out.println(searchUrl);
		connectHttp(searchUrl,"searchResult.txt");
		return true;
	}
	
	boolean checkVendorIsAmazon(){
		return false;
	}
	
}
