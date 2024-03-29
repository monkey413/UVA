/*uva10157*/
import java.util.Scanner ;
import java.math.BigInteger;
public class Main {
	  public static void main(String[] args)
	  {
	        Scanner cin = new Scanner(System.in);
	        BigInteger[][] F = new BigInteger[310][160];
	        
	        for(int i=0 ; i<=300 ; i++){
	        	for(int j=0 ; j<=150 ; j++){
	        		F[i][j] = new BigInteger("0") ; 
	        	}
	        }
	        
	        for(int j=0 ; j<=150 ; ++j){
	        	F[0][j] = new BigInteger("1") ;
	        }
	             
	        for(int i=2 ; i<=300 ; i+=2){
	        	for(int j=1 ; j<=150 ; j++){
	        		for(int k=0 ; k<i ; k+=2){
	        			F[i][j] = F[i][j].add(F[k][j-1].multiply(F[i-k-2][j])) ; 
	        		}
	        	}
	        }
	        
	        for(int i=0 ; i<15 ; i+=2){
	        	for(int j=0 ; j<15 ; ++j){
	        		System.out.printf("%3d ",F[i][j]) ;
	        	}
	        	System.out.println();
	        }
	        
	        while(cin.hasNext())
	        {
	            int n = cin.nextInt();
	            int d = cin.nextInt();
	            if(n % 2 == 1)
	                System.out.println("0");
	            else
	            {
	                System.out.println(F[n][d].add(F[n][d - 1].negate()));
	            }
	        }
	    }
}
