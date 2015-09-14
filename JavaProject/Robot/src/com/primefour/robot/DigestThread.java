package com.primefour.robot;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.CookieHandler;
import java.net.CookieManager;
import java.net.CookiePolicy;
import java.net.CookieStore;
import java.net.HttpURLConnection;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.NetworkInterface;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLDecoder;
import java.security.DigestInputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.Iterator;

import javax.xml.bind.DatatypeConverter;


public class DigestThread extends Thread {
	private String mFileName ;
	public DigestThread(String fileName){
		mFileName = fileName;
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
	
	
	public void TestURL2(){
		URL url;
		try {
			url = new URL("http://www.httprecipes.com");
			HttpURLConnection conn = (HttpURLConnection)url.openConnection();
			conn.setConnectTimeout(1000);
			conn.setReadTimeout(1000);
			conn.setDoOutput(true);
			InputStream is = conn.getInputStream();
			OutputStream os = conn.getOutputStream();
			conn.setRequestProperty("user-agent", "robot");
			String type = conn.getHeaderField("content-type");
			
		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e){
			e.printStackTrace();
		}
		
		
		
	}
	
	public void run(){
		try {
			FileInputStream	fin = new FileInputStream(mFileName);
			MessageDigest mg = MessageDigest.getInstance("SHA-256");
			DigestInputStream dg = new DigestInputStream(fin,mg);
			while (dg.read() != -1) ;
			dg.close();
			byte[] digest = mg.digest();
			StringBuilder result = new StringBuilder(mFileName);
			result.append(": ");
			result.append(DatatypeConverter.printHexBinary(digest));
			System.out.println(result);
			
			FileInputStream fin2 = new FileInputStream(mFileName);
			byte readData[] = new byte[1024];
			while(true){
				int ret = fin2.read(readData);
				System.out.println(ret);
				System.out.println(readData.toString());
				if (ret == -1){
					break;
				}
				
			}
			fin2.close();
			
			InputStreamReader ir = new InputStreamReader(new FileInputStream(mFileName));
			
			char charBuff[] =new char[1024];
			while(true){
				int ret = ir.read(charBuff);
				System.out.println(ret);
				System.out.println(charBuff);
				if(ret == -1){
					break;
				}
			}
			
			InetAddress[] ia = InetAddress.getAllByName("www.baidu.com");
			int i = 0;
			for (i = 0 ;i < ia.length ;i++){
				System.out.println(ia[i].toString());
			}
			
			System.out.println("Hello World!");
			
			byte[] address = {107, 23, (byte) 216, (byte) 196};
			InetAddress ia1 = InetAddress.getByAddress(address);
			InetAddress ia2 = InetAddress.getByAddress("www.baidu.com",address);
			System.out.println(ia1);
			System.out.println(ia2);
			InetAddress host = InetAddress.getByAddress(address);
			System.out.println(host);
			//NetworkInterface ni = NetworkInterface.getByName("wlan0");
			
			NetworkInterface ni = NetworkInterface.getByName("eth0");
			Enumeration<InetAddress> ei = ni.getInetAddresses();
			
			while(ei.hasMoreElements()){
				InetAddress em = ei.nextElement();
				System.out.println(em);
			}
			
			int ret = 0;
			URL url = new URL("http://news.sina.com.cn");
			/*
			URL url1 = new URL("http://www.amazon.de");
			URL turl = ClassLoader.getSystemResource("Hello.txt");
			System.out.println(turl);
			InputStream is = url1.openStream();
			FileOutputStream fo = new FileOutputStream("index.html");
			
			byte sbuff[] = new byte[1024];
			while((ret = is.read(sbuff)) != -1){
				System.out.println(sbuff.length + "ret = " + ret );
				fo.write(sbuff,0,ret);
			}
			*/
			System.out.println("End");
/*
			String input = "https://www.google.com/" + "search?hl=en&as_q=Java&as_epq=I%2FO";
			String output = URLDecoder.decode(input, "UTF-8");
			System.out.println(output);
			*/
			
			
			CookieManager manager = new CookieManager();
			manager.setCookiePolicy(CookiePolicy.ACCEPT_ORIGINAL_SERVER);
			CookieHandler.setDefault(manager);
			CookieStore store = manager.getCookieStore();
			
			URL testurl = new URL("http://www.httprecipes.com/");
			URLConnection sconn = testurl.openConnection();
			InputStream tis = sconn.getInputStream();
			//OutputStream tos = sconn.getOutputStream();
			
			BufferedInputStream btis = new BufferedInputStream(tis);
			
			//BufferedOutputStream btos = new BufferedOutputStream(tos);
			StringBuilder sb = new StringBuilder();
			byte read_buff[] = new byte[1024];
			while((ret = btis.read(read_buff)) != -1){
				if(ret != 0){
					sb.append(new String(read_buff,0,ret));
				}else{
					break;
				}
			}
			System.out.println(sb);
			System.out.println("Hello End");
			
			ArrayList<String> result1 = extractNoCase(sb.toString(),"<p>","</p>",10);
			if(!result1.isEmpty()){
				Iterator<String> it = result1.iterator();
				for(;it.hasNext();){
					System.out.println(it.next());
				}
			}
			
			FileInputStream fti = new FileInputStream("PeekTest.txt");
			PeekableInputStream pis = new PeekableInputStream(fti);
			int tcount = 0;
			while((ret = pis.read()) != -1){
				tcount ++;
				System.out.print(ret);
			}
			System.out.println("");
			System.out.println(tcount + "###end:w");
			pis.close();
			fti.close(); 
			
			FileInputStream ftt1 = new FileInputStream("PeekTest.txt");
			PeekableInputStream pis1 = new PeekableInputStream(ftt1);
			tcount = 0; 
			int pos = 0;
			while((ret = pis1.peek()) != -1){
				tcount ++; 
				System.out.print(ret);
				pis1.read();
			}
			System.out.println("");
			System.out.println(tcount + "###end:w");
			
			ftt1.close();
			pis1.close();
			
			
			FileInputStream ftt = new FileInputStream("PeekTest.txt");
			tcount = 0; 
			while((ret = ftt.read()) != -1){
				tcount ++; 
				System.out.print(ret);
			}
			ftt.close();
			System.out.println("");
			System.out.println(tcount + "###end:w");
			/*
			FileInputStream sm = new FileInputStream("Simple.html");
			HTMLParser hp = new HTMLParser(sm);
			advance(hp,"form",20);
			System.out.println("kkkkkk:");
			*/
			
			/*
			FileInputStream ism = new FileInputStream("Simple.html");
			HtmlPage ihp = new HtmlPage(ism);
			System.out.println(ihp.toString());
			*/
			
			URL ssm = new URL("http://www.baidu.com");//"http://www.manchestereveningnews.co.uk/");//http://news.sina.com.cn");
			HtmlPage ihp = new HtmlPage(ssm.openStream());
			System.out.println(ihp.toString());
			FileOutputStream aa = new FileOutputStream("parser.txt");
			aa.write(ihp.toString().getBytes());
		} catch (FileNotFoundException | NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private boolean advance(HTMLParser parse, String tag, int count) throws IOException {
		int ch;
		
		StringBuilder result = new StringBuilder();
		HTMLTag ht = null;
		while ((ch = parse.read()) != -1) {
			if (ch == 0) {
				if(ht != null && result.length() != 0){
					ht.setContent(result.toString());
					result.setLength(0);
				}
				System.out.println("##" + ht);
				
				ht = (HTMLTag) parse.getTag().clone();
				String name = ht.getName();
				if (name.equalsIgnoreCase(tag)) {
					count--;
					if (count <= 0)
						return true;
				}
			}else if(ch != -1){
				result.append((char)ch);
			}
		}
		return false;
	}

}
