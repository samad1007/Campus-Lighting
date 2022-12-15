
import java.io.*;
import java.util.*;
public class GoBackN {

 public static void main(String args[]) throws IOException
 {
  Scanner sc = new Scanner(System.in);
  
  System.out.print("Enter the Window Size: ");
  int window =sc.nextInt();
  
  boolean loop = true;
  int sent = 0;
  
  while(loop)
  {
   
   for(int i = 0; i < window; i++)
   {
    System.out.println("Frame " + sent + " has been transmitted.");
    sent++;
    if(sent == window)
     break;
   }
      System.out.println("Enter the last Acknowledgement received.");
   int ack = sc.nextInt();
   
   if(ack == window)
    loop = false;
   else
    sent = ack;
  }
   }
}
