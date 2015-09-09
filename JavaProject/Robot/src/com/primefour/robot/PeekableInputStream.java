package com.primefour.robot;

import java.io.IOException;
import java.io.InputStream;

public class PeekableInputStream extends InputStream {
	
	private InputStream mStream;
	private byte  mPeekBuff[];
	private int  mPeekBuffLength = 100;
	private int  mReadOffset = 0;
	private int  mBufferedLength =0; 
	
	public PeekableInputStream(InputStream is,int buffLength){
		mStream = is;
		mPeekBuffLength  = buffLength;
		mPeekBuff = new byte[mPeekBuffLength]; 
	}
	
	public PeekableInputStream(InputStream is){
		mStream = is;
		mPeekBuff = new byte[mPeekBuffLength]; 
	}
	@Override
	public int read() throws IOException {
		if(mReadOffset < mBufferedLength){
			return mPeekBuff[mReadOffset++];
		}else{
			int ret = mStream.read(mPeekBuff,0,mPeekBuffLength);
			if(ret != -1){
				mBufferedLength = ret;
				mReadOffset = 0;
				return mPeekBuff[mReadOffset++];
			}else{
				return -1;
			}
		}
	}
	
	public int peek() throws IOException{
		return peek(0);
	}
	
	public int peek(int pos) throws IOException {
		if(mReadOffset + pos >= mBufferedLength){
			byte tmp[] = new byte[mPeekBuffLength]; 
			int i = 0;
			int j = 0;
			for (i = mReadOffset ;i < mBufferedLength; i ++,j++){
				tmp[j] = mPeekBuff[i];
			}
			int ret = mStream.read(tmp,j,mPeekBuffLength-j);
			if (ret == -1){
				return -1;
			}else{
				mBufferedLength -= mReadOffset; 
				mBufferedLength += ret;
				mReadOffset = 0; 
				mPeekBuff = tmp;
			}
		}else{
			if(mReadOffset + pos >= mPeekBuffLength){
				System.out.println("#############" + (mReadOffset + pos));
				return -1;
			}
			if(mBufferedLength == 0){
				int ret = mStream.read(mPeekBuff,0,mPeekBuffLength);
				if(ret != -1){
					mBufferedLength += ret;
					mReadOffset = 0; 
				}else{
					return -1;
				}
			}
		}
		
		return mPeekBuff[mReadOffset + pos];
	}

}
