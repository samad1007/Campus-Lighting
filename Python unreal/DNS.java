import java.net.*;
import java.io.*;
import java.util.*;

public class DNS 
{
 public static void main(String[] args) 
 { 
    Scanner sc = new Scanner(System.in);
    try 
    {
     System.out.println("\n Enter Host Name ");
     String hname=sc.next();
     InetAddress address;
     address = InetAddress.getByName(hname);
     System.out.println("Host Name: " + address.getHostName());
     System.out.println("IP: " + address.getHostAddress());
    } 
    catch(IOException e) 
    {
     e.printStackTrace();
    }
   
  
 
 }
}

