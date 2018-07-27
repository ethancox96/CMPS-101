//Ethan Cox
//etecox
//pa1
//List.java
//Implements the ListADT

public class List
{
    private class Node{
        Object item;
        //int index;
        Node next;
        Node prev;
        
        public Node(Object h){
            item = h;
            //index = -1;
            next = prev = null;
        }
    }
    
    Node head;
    Node tail;
    Node cursor;
    int index;
    int numItems;
    
    public List(){
        head = null;
        tail = null;
        cursor = head;
        numItems = 0;
    }
    
    int length(){
        return numItems;
    }
    
    int index(){
        if (cursor != null)
            return index;
        else
            return -1;
    }
    
    Object head(){
        if (this.length() > 0)
            return head.item;
        else
            return -1;
    }
    
    Object back(){
        if (this.length() > 0)
            return tail.item;
        else
            return -1;
    }
    
    Object get(){
        if (this.length() > 0 && this.index() >= 0){
            return cursor.item;
        }
        else
            return -1;
    }
    
    public boolean equals(Object x){
        if (List.class.isAssignableFrom(x.getClass())){
            List L = (List)x;
            if ( L.numItems != this.numItems)
                return false;
            
            else{
                Node N = L.head;
                Node M = this.head;
                for (int i = 1; i <= numItems; i++){
                    if (N.item != M.item)
                        return false;
                }
            }
            return true;
        }
        else{
            return false;
        }
    }
    
    void clear(){
        head = null;
        tail = null;
        cursor = null;
        numItems = 0;
    }
    
    void moveFront(){
        if (this.length() > 0){
            cursor = head;
            index = 0;
        }
    }
    
    void moveBack(){
        if (this.length() > 0){
            cursor = tail;
            index = numItems;
        }
    }
    
    void movePrev(){
        if (cursor != null && cursor != head){
            cursor = cursor.prev;
            index--;
        }
        else if (cursor == head){
            index = -1;
            cursor = null;
        }
    }
    
    void moveNext(){
        if (cursor != null && cursor != tail){
            cursor = cursor.next;
            index++;
        }
        else if (cursor == tail){
            index = -1;
            cursor = null;
        }
    }
    
    void prepend(Object obj){
        Node oldHead = head;
        head = new Node(obj);
       
        if (oldHead != null){
            oldHead.prev = head;
            head.next = oldHead;
        }
        
        if (numItems == 0) {
            tail = head;
            index++;
        }
        
        numItems++;
    }
    
    void append(Object obj){
        Node oldTail = tail;
        tail = new Node(obj);
            
        if (oldTail != null){
            oldTail.next = tail;
            tail.prev = oldTail;
        }
            
        if (numItems == 0){
            head = tail;
            index++;
        }
            
        numItems++;
    }
    
    void insertBefore(Object obj){
        if (this.length() > 0 && index >= 0){
            Node N = cursor;
            if (N == this.head)
                prepend(obj);
            else{
                Node P = new Node(obj);
                P.next = N;
                P.prev = N.prev;
                N.prev.next = P;
                N.prev = P;
            }
        }
        numItems++;
    }
    
    void insertAfter(Object obj){
        if (this.length() > 0 && index >= 0){
            Node N = cursor;
            if (N == this.tail)
                append(obj);
            else{
                Node P = new Node(obj);
                P.prev = N;
                P.next = N.next;
                N.next.prev = P;
                N.next = P;
            }
        }
        numItems++;
    }
    
    void deleteFront(){
        if (this.length() > 0){
            head = head.next;
            head.prev = null;
        }
        numItems--;
    }
    
    void deleteBack(){
        if (this.length() > 0){
            tail = tail.prev;
            tail.next = null;
        }
        numItems--;
    }
    
    void delete(){
        Node N = cursor;
        N.next.prev = N.prev;
        N.prev.next = N.next;
        N = null;
        cursor = null;
        numItems--;
    }
    
    public String toString(){
        StringBuilder sb = new StringBuilder();
        Node N = head;
        while (N != null){
            sb.append("" + N.item).append(" ");
            N = N.next;
        }
        return new String(sb);
    }
    
}






