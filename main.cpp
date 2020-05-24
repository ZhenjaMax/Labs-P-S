#define SIZE_UNIT 8
#define OPERATORS "+-*/"

class CustomStack {
private:
    int count;
    int sizemData;
protected:
    int* mData;
public:
    CustomStack(){
        count=0;
        sizemData = SIZE_UNIT;
        mData = new int[sizemData];
    }
    ~CustomStack(){
        delete [] mData;
    }
    void extend(int n){
        int* newmData = new int[sizemData+n];
        for(int i=0; i<sizemData; i++) newmData[i] = mData[i];
        delete [] mData;
        mData = newmData;
        sizemData+=n;
        return;
    }
    void push(int val){
        if(count+1==sizemData) this->extend(SIZE_UNIT);
        mData[count] = val;
        count++;
        return;
    }
    void pop(){
        if(this->IsEmpty()) this->stop();
        count--;
        return;
    }
    int top(){
        if(this->IsEmpty()) this->stop();
        return mData[count-1];
    }
    size_t size(){
        return count;
    }
    bool IsEmpty(){
        if(count==0) return 1;
        return 0;
    }
    void print(){
        if(this->size()!=1) this->stop();
        else cout << mData[0];
        return;
    }
    void stop(){
        this->~CustomStack();
        printf("error");
        exit(0);
    }
};


char* readStringToSpace(){
    char* str = new char[16];
    char c;
    int i = 0;
    while(((c=getchar())!=EOF)&&(c!=' ')&&(c!='\n')){
        str[i] = c;
        i++;
    }
    if((c==EOF)&&(i==0)) return NULL;
    str[i] = '\0';
    return str;
}

char* strchr(const char* s, char c){
    while (*s != c) if (!*s++) return 0;
    return (char*)s;
}

int main(){
    CustomStack stack;
    char* str;
    while((str=readStringToSpace())!=NULL){
        if((strchr(OPERATORS, *str))&&(str[1]=='\0')){
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            char c = *str;
            switch(c){
                case '+':
                    stack.push(a+b);
                    break;
                case '-':
                    stack.push(a-b);
                    break;
                case '*':
                    stack.push(a*b);
                    break;
                case '/':
                    if(b==0) stack.stop();
                    stack.push(a/b);
                    break;
            }
        } else stack.push(atoi(str));
		delete [] str;
    }
    stack.print();
    return 0;
}