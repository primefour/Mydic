package com.primefour.robot;

import java.io.*;
import java.net.*;

public class SimpleWebServer{
    private ServerSocket serverSocket;
    public SimpleWebServer(int port){
        try{
        serverSocket = new ServerSocket(port);
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    public void run(){
        while(true){
            try{
                Socket clientConnect = serverSocket.accept();
                handleConnectSession(clientConnect);
            }catch (IOException e){
                e.printStackTrace();
            }
        }
    }

    private void handleConnectSession(Socket conn){
        try{
        InputStream is = conn.getInputStream();
        InputStreamReader inputReader = new InputStreamReader(is);
        BufferedReader in = new BufferedReader(inputReader);
        OutputStream os = conn.getOutputStream();
        PrintStream out = new PrintStream(os);

        System.out.println("**New Request **");
        String first = in.readLine();
        System.out.println(first);

        String line;

        do{
            line = in.readLine();
            System.out.println(line);
        }while(line != null && line.trim().length() > 0);

        out.println("HTTP/1.1 200 OK");
        out.println("");
        out.println("<html");
        out.println("<head><title>Simple Web Server </title></head>");
        out.println("<body>");
        out.println("<h1>Hello World</h1>");
        out.println("</body>");
        out.println("</html>");
        out.close();
        in.close();
        conn.close();
        }catch (IOException e){
            e.printStackTrace();
        }
    }

    public static void main(String args[]){
        //try{
            if(args.length < 1){
                System.out.println("Usage: java SimpleWebServer [port]");
            }else{
                int port ;
                try{
                    port = Integer.parseInt(args[0]);
                    SimpleWebServer server = new SimpleWebServer(port);
                    server.run();
                }catch (NumberFormatException e){
                    System.out.println("Invalide port number");
                }
            }
            /*
        }catch(IOException e){
            e.printStackTrace();
        }
        */
    }

}
