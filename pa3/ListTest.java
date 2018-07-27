//Ethan Cox
//etecox
//pa3
//ListTest.java
//Tests the ListADT interface

public class ListTest{
    public static void main(String[] args){
        List A = new List();
        List B = new List();
        List C = new List();
        
        for(int i=1; i<=20; i++){
            A.append(i);
            B.prepend(i);
            C.append(i);
        }
        System.out.println(A);
        System.out.println(B);
        
        for(A.moveFront(); A.index()>=0; A.moveNext()){
            System.out.print(A.get()+" ");
        }
        System.out.println();
        for(B.moveBack(); B.index()>=0; B.movePrev()){
            System.out.print(B.get()+" ");
        }
        System.out.println();
        
        System.out.println(A.equals(B));
        System.out.println(B.equals(C));
        System.out.println(C.equals(A));
        
        System.out.println(A.head());
        System.out.println(A.back());
        A.deleteFront();
        A.deleteBack();
        System.out.println(A.head());
        System.out.println(A.back());
        System.out.println(A);
        
        A.moveFront();
        for(int i=0; i<5; i++) A.moveNext(); // at index 5
        A.insertBefore(-1);                  // at index 6
        for(int i=0; i<9; i++) A.moveNext(); // at index 15
        A.insertAfter(-2);
        for(int i=0; i<5; i++) A.movePrev(); // at index 10
        A.delete();
        System.out.println(A);
        System.out.println(A.length());
        A.clear();
        System.out.println(A.length());
    }
}