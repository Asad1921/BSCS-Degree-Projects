#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<ctime>
#include<cstdlib>
#include<sstream>
using namespace std;

int to_int(const string& s){
    int r=0;
    for(size_t i=0;i<s.length();++i){
        if(s[i]>='0'&&s[i]<='9'){
            r=r*10+(s[i]-'0');
        }
    }
    return r;
}

string generateID(){
    string w[]={"Alpha","Beta","Cyber","Neo","Zeta","Nova","Sigma","Omega","Pulse","Vortex","Apex","Zen","Matrix","Quantum","Pixel"};
    return w[rand()%15]+w[rand()%15]+to_string(100+rand()%900);
}

string generateExaminerID(){
    return "EXM"+to_string(1000+rand()%9000);
}

string currentTime(){
    time_t n=time(0);
    char* d=ctime(&n);
    string s(d);
    if(!s.empty()&&s.back()=='\n')s.pop_back();
    return s;
}

void clearScreen(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressEnter(){
    cout<<endl<<"Press Enter to continue...";
    cin.ignore(1000,'\n');
    cin.get();
}

bool vectorContains(const vector<int>& v,int val){
    for(size_t i=0;i<v.size();i++)
    if(v[i]==val)
    return true;
    return false;
}

string escapePipe(const string& s){
    string r;
    for(size_t i=0;i<s.length();++i){
        if(s[i]=='|')r+="\\|";
        else r+=s[i];
    }
    return r;
}

string unescapePipe(const string& s){
    string r;
    for(size_t i=0;i<s.length();++i)
    {
        if(s[i]=='\\'&&i+1<s.length()&&s[i+1]=='|'){
            r+='|';++i;
        }else r+=s[i];
    }
    return r;
}

class Question{
public:
    int type=0;
    string text;
    string opt[4];
    int correct=-1;
    int durationMinutes=0;
    Question()=default;
    Question(int t,const string& txt,const string o[4],int c,int dur=0):type(t),text(txt),correct(c),durationMinutes(dur){
        for(int i=0;i<4;++i)opt[i]=o[i];
    }
};

class Student{
public:
    string name,email,id1,id2;
    bool used1=false,used2=false;
    int category=-1;
    string examinerId;
};

class Result{
public:
    string name,email,id,date;
    int category;
    int mcqMarks=0;
    int paragraphMarks=0;
    vector<string> paragraphAnswers;
    string examinerId;
};

class ExamSetting{
public:
    int duration=40;
};

class Examiner{
public:
    string id;
    string name;
    string email;
    string password;
    bool active=true;
    vector<int> allowedCategories;
};

class ExaminerData{
public:
    string examinerId;
    vector<Question> questionsPerCategory[6];
    ExamSetting settingsPerCategory[6];
    vector<Student> students;
    vector<Result> results;
};

class CygenticTestCenter{
private:
    vector<string> categories={
        "Cyber Security","Artificial Intelligence","Graphic Designing",
        "Data Science","Web Development","Software Engineering"
    };
    vector<Examiner> examiners;
    vector<ExaminerData> examinerDataList;
    const string HEAD_EMAIL="admin@cygenic.com";
    const string HEAD_PASS="head123#CTA";

    void saveCategories(){
        ofstream f("categories.txt");
        if(!f)return;
        for(size_t i=0;i<categories.size();i++)f<<categories[i]<<endl;
    }

    void loadCategories(){
        ifstream f("categories.txt");
        if(!f)return;
        categories.clear();
        string l;
        while(getline(f,l))if(!l.empty())categories.push_back(l);
    }

    string getExaminerFileName(const string& exId)const{
        return "examiner_"+exId+".txt";
    }

    ExaminerData* findExaminerData(const string& exId){
        for(size_t i=0;i<examinerDataList.size();i++)
            if(examinerDataList[i].examinerId==exId)return &examinerDataList[i];
        return nullptr;
    }

    void saveExaminerData(const string& exId){
        ExaminerData* d=findExaminerData(exId);
        if(!d)return;
        ofstream f(getExaminerFileName(exId));
        if(!f)return;
        f<<"[QUESTIONS]"<<endl;
        for(int cat=0;cat<6;++cat){
            for(size_t i=0;i<d->questionsPerCategory[cat].size();i++){
                const Question& q=d->questionsPerCategory[cat][i];
                f<<cat<<"|"<<q.type<<"|"<<escapePipe(q.text)<<"|";
                if(q.type==0){
                    f<<escapePipe(q.opt[0])<<"|"
                    <<escapePipe(q.opt[1])<<"|"
                    <<escapePipe(q.opt[2])<<"|"
                    <<escapePipe(q.opt[3])<<"|"
                    <<q.correct<<"|";
                }
                f<<q.durationMinutes<<endl;
            }
        }
        f<<"[SETTINGS]"<<endl;
        for(int cat=0;cat<6;++cat){
            f<<cat<<"|"<<d->settingsPerCategory[cat].duration<<endl;
        }
        f<<"[STUDENTS]"<<endl;
        for(size_t i=0;i<d->students.size();i++){
            const Student& s=d->students[i];
            f<<escapePipe(s.name)<<"|"<<escapePipe(s.email)<<"|"
            <<s.id1<<"|"<<s.id2<<"|"
            <<(s.used1?"1":"0")<<"|"<<(s.used2?"1":"0")<<"|"
            <<s.category<<endl;
        }
        f<<"[RESULTS]"<<endl;
        for(size_t i=0;i<d->results.size();i++){
            const Result& r=d->results[i];
            f<<escapePipe(r.name)<<"|"<<escapePipe(r.email)<<"|"
            <<r.id<<"|"<<escapePipe(r.date)<<"|"
            <<r.category<<"|"<<r.mcqMarks<<"|"<<r.paragraphAnswers.size();
            for(size_t j=0;j<r.paragraphAnswers.size();j++)
                f<<"|"<<escapePipe(r.paragraphAnswers[j]);
            f<<"|"<<r.paragraphMarks<<endl;
        }
    }

    void loadExaminerData(const string& exId){
        ExaminerData* d=findExaminerData(exId);
        if(!d)return;
        ifstream f(getExaminerFileName(exId));
        if(!f)return;
        string l,sec;
        while(getline(f,l)){
            if(l.empty())continue;
            if(l[0]=='['){sec=l;continue;}
            stringstream ss(l);
            vector<string> p;
            string t;
            while(getline(ss,t,'|'))p.push_back(t);
            if(sec=="[QUESTIONS]"&&p.size()>=8){
                int cat=to_int(p[0]);
                Question q;
                q.type=to_int(p[1]);
                q.text=unescapePipe(p[2]);
                if(q.type==0){
                    q.opt[0]=unescapePipe(p[3]);
                    q.opt[1]=unescapePipe(p[4]);
                    q.opt[2]=unescapePipe(p[5]);
                    q.opt[3]=unescapePipe(p[6]);
                    q.correct=to_int(p[7]);
                }
                q.durationMinutes=to_int(p.back());
                if(cat>=0&&cat<6)d->questionsPerCategory[cat].push_back(q);
            }
            else if(sec=="[SETTINGS]"&&p.size()==2){
                int cat=to_int(p[0]);
                d->settingsPerCategory[cat].duration=to_int(p[1]);
            }
            else if(sec=="[STUDENTS]"&&p.size()==7){
                Student s;
                s.name=unescapePipe(p[0]);
                s.email=unescapePipe(p[1]);
                s.id1=p[2];s.id2=p[3];
                s.used1=(p[4]=="1");
                s.used2=(p[5]=="1");
                s.category=to_int(p[6]);
                s.examinerId=exId;
                d->students.push_back(s);
            }
            else if(sec=="[RESULTS]"&&p.size()>=8){
                Result r;
                r.name=unescapePipe(p[0]);
                r.email=unescapePipe(p[1]);
                r.id=p[2];
                r.date=unescapePipe(p[3]);
                r.category=to_int(p[4]);
                r.mcqMarks=to_int(p[5]);
                size_t ansC=to_int(p[6]);
                size_t idx=7;
                for(size_t i=0;i<ansC;++i)r.paragraphAnswers.push_back(unescapePipe(p[idx++]));
                r.paragraphMarks=to_int(p[idx]);
                r.examinerId=exId;
                d->results.push_back(r);
            }
        }
    }

    void saveExaminersList(){
        ofstream f("examiners_list.txt");
        if(!f)return;
        for(size_t i=0;i<examiners.size();i++){
            const Examiner& e=examiners[i];
            f<<e.id<<"|"<<e.name<<"|"<<e.email<<"|"<<e.password<<"|"<<(e.active?"1":"0");
            for(size_t j=0;j<e.allowedCategories.size();j++)f<<"|"<<e.allowedCategories[j];
            f<<endl;
        }
    }

    void loadExaminersList(){
        ifstream f("examiners_list.txt");
        if(!f)return;
        string l;
        while(getline(f,l)){
            stringstream ss(l);
            vector<string> p;
            string t;
            while(getline(ss,t,'|'))p.push_back(t);
            if(p.size()<5)continue;
            Examiner e;
            e.id=p[0];e.name=p[1];e.email=p[2];e.password=p[3];
            e.active=(p[4]=="1");
            for(size_t i=5;i<p.size();++i)e.allowedCategories.push_back(to_int(p[i]));
            examiners.push_back(e);
            ExaminerData nd;
            nd.examinerId=e.id;
            examinerDataList.push_back(nd);
            loadExaminerData(e.id);
        }
    }

    void addDefaultQuestions(int cat,vector<Question>& qs){
        qs.clear();
        if(cat==0){
            string o1[4]={"80","443","21","22"};
            string o2[4]={"Fake email to steal data","Fishing","Hardware attack","None"};
            string o3[4]={"DES","AES-256","MD5","SHA-1"};
            string o4[4]={"Unauthorized access","Emails","Games","Rain"};
            string o5[4]={"Name","IP Address","Password","All"};
            string o6[4]={"Encrypts files for ransom","Deletes files","Speeds PC","Free"};
            string o7[4]={"Guessing passwords","Physical break","DDoS","SQL"};
            string o8[4]={"Two passwords","Password + OTP","Two emails","None"};
            string o9[4]={"Database","Network","Printer","Mouse"};
            string o10[4]={"Denial of Service","Data Delete","Download","None"};
            string o11[4]={"ISP","Browser history","Website","All"};
            string o12[4]={"123456","name123","P@ssw0rd2025!","password"};
            string o13[4]={"Exploit before patch","Midnight attack","None","All"};
            string o14[4]={"Fake identity","Cooking","Running","None"};
            string o15[4]={"Eavesdropping","Fighting","None","All"};
            string o16[4]={"Fingerprint/Voice","Password only","Email","None"};
            string o17[4]={"Malware","Heat","Rain","All"};
            string o18[4]={"FTP","SSH","HTTP","SMTP"};
            string o19[4]={"SSL/TLS","VPN","Firewall","None"};
            string o20[4]={"Share password","Use same everywhere","Use password manager","Write on paper"};
            qs.push_back(Question(0,"HTTPS uses which port?",o1,1,0));
            qs.push_back(Question(0,"What is Phishing?",o2,0,0));
            qs.push_back(Question(0,"Strongest encryption?",o3,1,0));
            qs.push_back(Question(0,"Firewall blocks?",o4,0,0));
            qs.push_back(Question(0,"VPN hides your?",o5,1,0));
            qs.push_back(Question(0,"Ransomware?",o6,0,0));
            qs.push_back(Question(0,"Brute force = ?",o7,0,0));
            qs.push_back(Question(0,"2FA means?",o8,1,0));
            qs.push_back(Question(0,"SQL Injection attacks?",o9,0,0));
            qs.push_back(Question(0,"DDoS = ?",o10,0,0));
            qs.push_back(Question(0,"Incognito hides from?",o11,1,0));
            qs.push_back(Question(0,"Best password?",o12,2,0));
            qs.push_back(Question(0,"Zero-day attack?",o13,0,0));
            qs.push_back(Question(0,"Spoofing = ?",o14,0,0));
            qs.push_back(Question(0,"Man-in-the-Middle?",o15,0,0));
            qs.push_back(Question(0,"Biometric uses?",o16,0,0));
            qs.push_back(Question(0,"Antivirus protects from?",o17,0,0));
            qs.push_back(Question(0,"Port 22 used by?",o18,1,0));
            qs.push_back(Question(0,"HTTPS = HTTP + ?",o19,0,0));
            qs.push_back(Question(0,"Best practice?",o20,2,0));
        }
        else if(cat==1){
            string o1[4]={"Alan Turing","John McCarthy","Elon Musk","Bill Gates"};
            string o2[4]={"AI","Robotics","Networking","Hardware"};
            string o3[4]={"Human brain","Chip","Internet","Phone"};
            string o4[4]={"Rules","Deep Learning","If-else","None"};
            string o5[4]={"Memorizes data","Too simple","Perfect","None"};
            string o6[4]={"Labeled data","No data","Images only","Voice"};
            string o7[4]={"Generative Adversarial Network","Good AI","Game AI","None"};
            string o8[4]={"Chess","Go","Cricket","Football"};
            string o9[4]={"Google","Microsoft","Apple","Meta"};
            string o10[4]={"Natural Language Processing","New Programming","Neural Link","None"};
            string o11[4]={"Speed","Human-like thinking","Strength","Vision"};
            string o12[4]={"Strong","Narrow AI","Super AI","None"};
            string o13[4]={"Rewards","Books","Teacher","Copy"};
            string o14[4]={"Seeing","Hearing","Smelling","Tasting"};
            string o15[4]={"Virtual Assistant","Robot","Game","Virus"};
            string o16[4]={"Bad data","Fast CPU","Good data","None"};
            string o17[4]={"Kasparov (Chess)","Lee Sedol (Go)","None","Both"};
            string o18[4]={"Artificial General Intelligence","Advanced GPU","All Good","None"};
            string o19[4]={"Narrow AI","Strong AI","Super AI","None"};
            string o20[4]={"1956 Dartmouth","2020","1990","None"};
            qs.push_back(Question(0,"Father of AI?",o1,1,0));
            qs.push_back(Question(0,"ML is subset of?",o2,0,0));
            qs.push_back(Question(0,"Neural Network inspired by?",o3,0,0));
            qs.push_back(Question(0,"ChatGPT uses?",o4,1,0));
            qs.push_back(Question(0,"Overfitting = ?",o5,0,0));
            qs.push_back(Question(0,"Supervised Learning needs?",o6,0,0));
            qs.push_back(Question(0,"GAN = ?",o7,0,0));
            qs.push_back(Question(0,"AlphaGo plays?",o8,1,0));
            qs.push_back(Question(0,"TensorFlow by?",o9,0,0));
            qs.push_back(Question(0,"NLP = ?",o10,0,0));
            qs.push_back(Question(0,"Turing Test checks?",o11,1,0));
            qs.push_back(Question(0,"Current AI is?",o12,1,0));
            qs.push_back(Question(0,"Reinforcement Learning learns by?",o13,0,0));
            qs.push_back(Question(0,"Computer Vision for?",o14,0,0));
            qs.push_back(Question(0,"Siri/Alexa = ?",o15,0,0));
            qs.push_back(Question(0,"AI Bias from?",o16,0,0));
            qs.push_back(Question(0,"Deep Blue defeated?",o17,0,0));
            qs.push_back(Question(0,"AGI = ?",o18,0,0));
            qs.push_back(Question(0,"Weak AI also called?",o19,0,0));
            qs.push_back(Question(0,"First AI conference?",o20,0,0));
        }
        else if(cat==2){
            string o1[4]={"Print","Screen","Both","None"};
            string o2[4]={"Screen","Print","Web","Mobile"};
            string o3[4]={"Transparency","Animation","Both","None"};
            string o4[4]={"Pixel-based","Scalable forever","Heavy","Low quality"};
            string o5[4]={"1.618","2.718","3.14","1.414"};
            string o6[4]={"Space between letters","Line height","Color","Size"};
            string o7[4]={"Pixels","Paths","Lines","Shapes"};
            string o8[4]={"72 DPI","300 DPI","150 DPI","600 DPI"};
            string o9[4]={"Vector","Raster","Both","None"};
            string o10[4]={"Illustrator","Photoshop","Both","None"};
            string o11[4]={"RGB","CMY","Red Yellow Blue","All"};
            string o12[4]={"Drawing","Arranging type","Coding","None"};
            string o13[4]={"Vector format","Raster","Audio","Video"};
            string o14[4]={"Composition","Color","Size","All"};
            string o15[4]={"Empty area","Black","Background","None"};
            string o16[4]={"Small lines at ends","No lines","Script","None"};
            string o17[4]={"Opposite on wheel","Next to each other","Triadic","None"};
            string o18[4]={"Line spacing","Letter spacing","Font size","None"};
            string o19[4]={"JPG","PNG","SVG","GIF"};
            string o20[4]={"Readability","Speed","Size","All"};
            qs.push_back(Question(0,"RGB for?",o1,1,0));
            qs.push_back(Question(0,"CMYK for?",o2,1,0));
            qs.push_back(Question(0,"PNG supports?",o3,0,0));
            qs.push_back(Question(0,"Vector graphics?",o4,1,0));
            qs.push_back(Question(0,"Golden Ratio ≈?",o5,0,0));
            qs.push_back(Question(0,"Kerning = ?",o6,0,0));
            qs.push_back(Question(0,"Raster = ?",o7,0,0));
            qs.push_back(Question(0,"Print resolution?",o8,1,0));
            qs.push_back(Question(0,"Photoshop is?",o9,1,0));
            qs.push_back(Question(0,"Bezier curves in?",o10,2,0));
            qs.push_back(Question(0,"Primary pigment colors?",o11,2,0));
            qs.push_back(Question(0,"Typography = art of?",o12,1,0));
            qs.push_back(Question(0,"SVG = ?",o13,0,0));
            qs.push_back(Question(0,"Rule of thirds for?",o14,0,0));
            qs.push_back(Question(0,"Negative space = ?",o15,0,0));
            qs.push_back(Question(0,"Serif font has?",o16,0,0));
            qs.push_back(Question(0,"Complementary colors are?",o17,0,0));
            qs.push_back(Question(0,"Leading = ?",o18,0,0));
            qs.push_back(Question(0,"Best for logo?",o19,2,0));
            qs.push_back(Question(0,"Alignment improves?",o20,0,0));
        }
        else if(cat==3){
            string o1[4]={"Python","Java","C++","JS"};
            string o2[4]={"Numerical arrays","Web","Games","None"};
            string o3[4]={"Outliers","Median","Mode","None"};
            string o4[4]={"-1 to +1","0 to 100","1 to 10","None"};
            string o5[4]={"More data","Regularization","Both","None"};
            string o6[4]={"Machine Learning","Web","Design","None"};
            string o7[4]={"Significant","Not significant","Error","None"};
            string o8[4]={"Databases","Web pages","Design","None"};
            string o9[4]={"Volume Velocity Variety","Speed Size Cost","All","None"};
            string o10[4]={"Interactive Python","Web","Games","None"};
            string o11[4]={"Exploratory Data Analysis","Easy Data Access","None","All"};
            string o12[4]={"Outliers","Mean","Correlation","None"};
            string o13[4]={"Categories","Continuous values","Both","None"};
            string o14[4]={"Numbers","Categories","Both","None"};
            string o15[4]={"Supervised","Unsupervised","Reinforcement","None"};
            string o16[4]={"Dimensionality reduction","Speed","Accuracy","None"};
            string o17[4]={"Correct/Total","True Positive","None","All"};
            string o18[4]={"TP/(TP+FP)","TP/(TP+FN)","None","All"};
            string o19[4]={"TP/(TP+FN)","TP/(TP+FP)","None","All"};
            string o20[4]={"Visualization","Data cleaning","Modeling","None"};
            qs.push_back(Question(0,"Pandas library for?",o1,0,0));
            qs.push_back(Question(0,"NumPy for?",o2,0,0));
            qs.push_back(Question(0,"Mean affected by?",o3,0,0));
            qs.push_back(Question(0,"Correlation range?",o4,0,0));
            qs.push_back(Question(0,"Overfitting fixed by?",o5,2,0));
            qs.push_back(Question(0,"Scikit-learn for?",o6,0,0));
            qs.push_back(Question(0,"p-value < 0.05 = ?",o7,0,0));
            qs.push_back(Question(0,"SQL for?",o8,0,0));
            qs.push_back(Question(0,"Big Data 3V?",o9,0,0));
            qs.push_back(Question(0,"Jupyter for?",o10,0,0));
            qs.push_back(Question(0,"EDA means?",o11,0,0));
            qs.push_back(Question(0,"Box plot shows?",o12,0,0));
            qs.push_back(Question(0,"Regression predicts?",o13,1,0));
            qs.push_back(Question(0,"Classification predicts?",o14,1,0));
            qs.push_back(Question(0,"K-Means is?",o15,1,0));
            qs.push_back(Question(0,"PCA for?",o16,0,0));
            qs.push_back(Question(0,"Accuracy = ?",o17,0,0));
            qs.push_back(Question(0,"Precision = ?",o18,0,0));
            qs.push_back(Question(0,"Recall = ?",o19,0,0));
            qs.push_back(Question(0,"Matplotlib for?",o20,0,0));
        }
        else if(cat==4){
            string o1[4]={"HyperText Markup Language","HighText","HomeTool","None"};
            string o2[4]={"Structure","Styling","Logic","Database"};
            string o3[4]={"Server","Client","Both","None"};
            string o4[4]={"Block","Inline","Both","None"};
            string o5[4]={"HTML","CSS","JS","None"};
            string o6[4]={"Media queries","Fixed width","Both","None"};
            string o7[4]={"Image","Video","Text","Link"};
            string o8[4]={"Search Engine Optimization","Speed","Design","None"};
            string o9[4]={"On server","On browser","RAM","None"};
            string o10[4]={"Framework","Language","Editor","None"};
            string o11[4]={"OK","Not Found","Server Error","Redirect"};
            string o12[4]={"Document Object Model","Design","Data","None"};
            string o13[4]={"Library","Framework","Language","None"};
            string o14[4]={"Frontend","Backend","Both","None"};
            string o15[4]={"HTTP methods","FTP","SMTP","None"};
            string o16[4]={"JavaScript Object Notation","Text","Image","None"};
            string o17[4]={"Mobile responsiveness","Speed","Color","None"};
            string o18[4]={"HTML","CSS","JS","None"};
            string o19[4]={"<header><footer>","<div>","Both","None"};
            string o20[4]={"JPG","PNG","SVG","GIF"};
            qs.push_back(Question(0,"HTML stands for?",o1,0,0));
            qs.push_back(Question(0,"CSS for?",o2,1,0));
            qs.push_back(Question(0,"JavaScript runs on?",o3,2,0));
            qs.push_back(Question(0,"<div> is?",o4,0,0));
            qs.push_back(Question(0,"Flexbox part of?",o5,1,0));
            qs.push_back(Question(0,"Responsive design uses?",o6,0,0));
            qs.push_back(Question(0,"<img> tag for?",o7,0,0));
            qs.push_back(Question(0,"SEO means?",o8,0,0));
            qs.push_back(Question(0,"LocalStorage saves?",o9,1,0));
            qs.push_back(Question(0,"Bootstrap is?",o10,0,0));
            qs.push_back(Question(0,"HTTP 404?",o11,1,0));
            qs.push_back(Question(0,"DOM stands for?",o12,0,0));
            qs.push_back(Question(0,"React is?",o13,0,0));
            qs.push_back(Question(0,"Node.js for?",o14,1,0));
            qs.push_back(Question(0,"REST API uses?",o15,0,0));
            qs.push_back(Question(0,"JSON format?",o16,0,0));
            qs.push_back(Question(0,"Viewport meta tag for?",o17,0,0));
            qs.push_back(Question(0,"Grid layout in?",o18,1,0));
            qs.push_back(Question(0,"Semantic tags?",o19,0,0));
            qs.push_back(Question(0,"Best for web icons?",o20,2,0));
        }
        else if(cat==5){
            string o1[4]={"Sequential","Iterative","Both","None"};
            string o2[4]={"Documentation","Working software","Plans","Meetings"};
            string o3[4]={"Sprints","Waterfalls","Both","None"};
            string o4[4]={"Unified Modeling Language","User","Universal","None"};
            string o5[4]={"Inheritance","Copy-paste","Both","None"};
            string o6[4]={"Unit Integration System","Only unit","None","All"};
            string o7[4]={"Internal code","Input/output","Both","None"};
            string o8[4]={"Planning Analysis Design...","Only coding","None","All"};
            string o9[4]={"Git","Word","Notepad","None"};
            string o10[4]={"Continuous Integration Delivery","Copy Install","None","All"};
            string o11[4]={"Improve code without changing behavior","Rewrite","Delete","None"};
            string o12[4]={"Time complexity","Space","Both","None"};
            string o13[4]={"Model View Controller","Model View Code","None","All"};
            string o14[4]={"Two developers","One","None","All"};
            string o15[4]={"Quality","Speed","Both","None"};
            string o16[4]={"Bug = found Error = not found","Same","None","All"};
            string o17[4]={"Robert Martin","Bill Gates","None","All"};
            string o18[4]={"Test Driven Development","Try Debug Delete","None","All"};
            string o19[4]={"Small independent services","Monolith","Both","None"};
            string o20[4]={"Copy-paste","Write reusable code","Both","None"};
            qs.push_back(Question(0,"Waterfall model?",o1,0,0));
            qs.push_back(Question(0,"Agile focuses on?",o2,1,0));
            qs.push_back(Question(0,"Scrum has?",o3,0,0));
            qs.push_back(Question(0,"UML stands for?",o4,0,0));
            qs.push_back(Question(0,"OOP principle?",o5,0,0));
            qs.push_back(Question(0,"Testing types?",o6,0,0));
            qs.push_back(Question(0,"Black box testing?",o7,1,0));
            qs.push_back(Question(0,"SDLC phases?",o8,0,0));
            qs.push_back(Question(0,"Version control?",o9,0,0));
            qs.push_back(Question(0,"CI/CD means?",o10,0,0));
            qs.push_back(Question(0,"Refactoring = ?",o11,0,0));
            qs.push_back(Question(0,"Big O notation for?",o12,2,0));
            qs.push_back(Question(0,"MVC pattern?",o13,0,0));
            qs.push_back(Question(0,"Pair programming?",o14,0,0));
            qs.push_back(Question(0,"Code review improves?",o15,0,0));
            qs.push_back(Question(0,"Bug vs Error?",o16,0,0));
            qs.push_back(Question(0,"SOLID principles by?",o17,0,0));
            qs.push_back(Question(0,"TDD = ?",o18,0,0));
            qs.push_back(Question(0,"Microservices?",o19,0,0));
            qs.push_back(Question(0,"Best practice?",o20,1,0));
        }
    }

    int getOrCreateCategory(Examiner& ex){
        while(true){
            clearScreen();
            cout<<"AVAILABLE CATEGORIES:"<<endl;
            for(size_t i=0;i<categories.size();++i){
                string a=vectorContains(ex.allowedCategories,static_cast<int>(i))?"":" (No access yet)";
                cout<<i<<". "<<categories[i]<<a<<endl;
            }
            cout<<categories.size()<<". Add New Category"<<endl;
            cout<<"Enter category number: ";
            string in;
            getline(cin,in);
            int ch=-1;
            stringstream ss(in);
            ss>>ch;
            if(ch==static_cast<int>(categories.size())){
                cout<<"Enter new category name: ";
                string n;
                getline(cin,n);
                if(n.empty())continue;
                categories.push_back(n);
                saveCategories();
                int ni=categories.size()-1;
                ex.allowedCategories.push_back(ni);
                cout<<"New category created: "<<n<<endl;
                return ni;
            }
            if(ch>=0&&ch<static_cast<int>(categories.size())&&vectorContains(ex.allowedCategories,ch)){
                return ch;
            }
            cout<<"Invalid choice or no access!"<<endl;
            pressEnter();
        }
    }

    Examiner* getExaminerById(const string& id){
        for(size_t i=0;i<examiners.size();i++)
            if(examiners[i].id==id)return &examiners[i];
        return nullptr;
    }

public:
    CygenticTestCenter(){
        srand(time(nullptr));
        loadCategories();
        loadExaminersList();
    }

    ~CygenticTestCenter(){
        for(size_t i=0;i<examinerDataList.size();i++)
            saveExaminerData(examinerDataList[i].examinerId);
        saveExaminersList();
        saveCategories();
    }

    void run(){
        mainMenu();
    }

private:
    void mainMenu();
    void headAdminMenu();
    void examinerMenu(const string& examinerId);
    void studentExam(const string& testId);
};

void CygenticTestCenter::mainMenu(){
    while(true){
        clearScreen();
        cout<<"=== CYGENTIC TEST CENTER ==="<<endl;
        cout<<"1. Head Admin Login"<<endl;
        cout<<"2. Examiner Login"<<endl;
        cout<<"3. Student Login (Enter Test ID)"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Choice: ";
        int ch;
        cin>>ch;
        cin.ignore(1000,'\n');
        if(ch==1){
            clearScreen();
            cout<<"HEAD ADMIN LOGIN"<<endl;
            string e,p;
            cout<<"Email: ";getline(cin,e);
            cout<<"Password: ";getline(cin,p);
            if(e==HEAD_EMAIL&&p==HEAD_PASS){
                headAdminMenu();
            }else{
                cout<<"Invalid Credentials!"<<endl;
                pressEnter();
            }
        }
        else if(ch==2){
            clearScreen();
            cout<<"EXAMINER LOGIN"<<endl;
            string e,p,u;
            cout<<"Email: ";getline(cin,e);
            cout<<"Password: ";getline(cin,p);
            cout<<"Unique ID: ";getline(cin,u);
            bool f=false;
            for(size_t i=0;i<examiners.size();i++){
                if(examiners[i].email==e&&examiners[i].password==p&&examiners[i].id==u&&examiners[i].active){
                    examinerMenu(examiners[i].id);
                    f=true;
                    break;
                }
            }
            if(!f){
                cout<<"Invalid Login or Account Inactive!"<<endl;
                pressEnter();
            }
        }
        else if(ch==3){
            clearScreen();
            cout<<"STUDENT LOGIN"<<endl;
            string id;
            cout<<"Enter your Test ID: ";getline(cin,id);
            bool v=false;
            string exId;
            Student* sel=nullptr;
            for(size_t i=0;i<examinerDataList.size();i++){
                for(size_t j=0;j<examinerDataList[i].students.size();j++){
                    Student& s=examinerDataList[i].students[j];
                    if((s.id1==id&&!s.used1)||(s.id2==id&&!s.used2)){
                        if(s.id1==id)s.used1=true;
                        else s.used2=true;
                        sel=&s;
                        exId=examinerDataList[i].examinerId;
                        v=true;
                        break;
                    }
                }
                if(v)break;
            }
            if(v&&sel){
                cout<<"Welcome, "<<sel->name<<"!"<<endl;
                cout<<"Category: "<<categories[sel->category]<<endl<<endl;
                pressEnter();
                studentExam(id);
                saveExaminerData(exId);
            }else{
                cout<<"Invalid or Already Used Test ID!"<<endl;
                pressEnter();
            }
        }
        else if(ch==4){
            clearScreen();
            cout<<"THANK YOU FOR USING CYGENTIC TEST CENTER"<<endl;
            break;
        }
    }
}

void CygenticTestCenter::headAdminMenu(){
    while(true){
        clearScreen();
        cout<<"HEAD ADMIN DASHBOARD"<<endl;
        cout<<"1. Manage Categories"<<endl;
        cout<<"2. Manage Examiners"<<endl;
        cout<<"3. View All Results"<<endl;
        cout<<"4. Back to Main Menu"<<endl;
        cout<<"Choice: ";
        int ch;
        cin>>ch;
        cin.ignore(1000,'\n');
        if(ch==1){
            clearScreen();
            cout<<"MANAGE CATEGORIES"<<endl;
            for(size_t i=0;i<categories.size();++i)
                cout<<i<<". "<<categories[i]<<endl;
            cout<<endl<<"Add new category (leave blank to cancel): ";
            string n;
            getline(cin,n);
            if(!n.empty()){
                categories.push_back(n);
                saveCategories();
                cout<<"Category Added Successfully!"<<endl;
            }
            pressEnter();
        }
        else if(ch==2){
            clearScreen();
            cout<<"MANAGE EXAMINERS"<<endl;
            cout<<"1. View All Examiners"<<endl;
            cout<<"2. Add New Examiner"<<endl;
            cout<<"3. Back"<<endl;
            cout<<"Choice: ";
            int c;
            cin>>c;
            cin.ignore(1000,'\n');
            if(c==1){
                clearScreen();
                cout<<"ALL EXAMINERS"<<endl;
                if(examiners.empty()){
                    cout<<"No examiners registered yet."<<endl;
                }else{
                    for(size_t i=0;i<examiners.size();i++){
                        cout<<(i+1)<<". "<<examiners[i].name<<" ("<<examiners[i].id<<")"<<endl;
                        cout<<"   Email: "<<examiners[i].email<<endl;
                        cout<<"   Status: "<<(examiners[i].active?"Active":"Inactive")<<endl;
                        cout<<"   Categories: ";
                        for(size_t j=0;j<examiners[i].allowedCategories.size();j++){
                            cout<<categories[examiners[i].allowedCategories[j]];
                            if(j<examiners[i].allowedCategories.size()-1)cout<<", ";
                        }
                        cout<<endl<<endl;
                    }
                }
                pressEnter();
            }
            else if(c==2){
                clearScreen();
                cout<<"ADD NEW EXAMINER"<<endl;
                Examiner ne;
                cout<<"Name: ";getline(cin,ne.name);
                cout<<"Email: ";getline(cin,ne.email);
                cout<<"Password: ";getline(cin,ne.password);
                ne.id=generateExaminerID();
                ne.active=true;
                cout<<endl<<"Assign categories (enter numbers, -1 to stop):"<<endl;
                for(size_t i=0;i<categories.size();++i)
                    cout<<i<<". "<<categories[i]<<endl;
                while(true){
                    int cat;
                    cout<<"Category number (-1 to stop): ";
                    cin>>cat;
                    cin.ignore(1000,'\n');
                    if(cat==-1)break;
                    if(cat>=0&&cat<static_cast<int>(categories.size())){
                        if(!vectorContains(ne.allowedCategories,cat))
                            ne.allowedCategories.push_back(cat);
                    }
                }
                examiners.push_back(ne);
                ExaminerData nd;
                nd.examinerId=ne.id;
                cout<<endl<<"Load default questions? (y/n): ";
                string r;
                getline(cin,r);
                if(!r.empty()&&(r[0]=='y'||r[0]=='Y')){
                    for(size_t i=0;i<ne.allowedCategories.size();i++){
                        int cat=ne.allowedCategories[i];
                        addDefaultQuestions(cat,nd.questionsPerCategory[cat]);
                    }
                    cout<<"Default questions loaded for all allowed categories!"<<endl;
                }
                examinerDataList.push_back(nd);
                saveExaminersList();
                saveExaminerData(ne.id);
                cout<<endl<<"Examiner created successfully!"<<endl;
                cout<<"Examiner ID: "<<ne.id<<endl;
                cout<<"Name: "<<ne.name<<endl;
                cout<<"Email: "<<ne.email<<endl;
                pressEnter();
            }
        }
        else if(ch==3){
            clearScreen();
            cout<<"VIEW ALL RESULTS"<<endl<<endl;
            bool f=false;
            for(size_t i=0;i<examinerDataList.size();i++){
                ExaminerData& d=examinerDataList[i];
                Examiner* ex=getExaminerById(d.examinerId);
                string en=ex?ex->name:"Unknown";
                for(size_t j=0;j<d.results.size();j++){
                    f=true;
                    Result& r=d.results[j];
                    cout<<"Examiner: "<<en<<endl;
                    cout<<"Student: "<<r.name<<" ("<<r.email<<")"<<endl;
                    cout<<"Category: "<<categories[r.category]<<endl;
                    cout<<"MCQ Score: "<<r.mcqMarks<<"%"<<endl;
                    cout<<"Paragraph Score: "<<r.paragraphMarks<<endl;
                    cout<<"Date: "<<r.date<<endl;
                    cout<<"------------------------"<<endl;
                }
            }
            if(!f)cout<<"No results available yet."<<endl;
            pressEnter();
        }
        else if(ch==4){
            break;
        }
        else{
            cout<<"Invalid choice!"<<endl;
            pressEnter();
        }
    }
}

void CygenticTestCenter::examinerMenu(const string& examinerId){
    Examiner* ex=getExaminerById(examinerId);
    if(!ex)return;
    ExaminerData* d=findExaminerData(examinerId);
    if(!d)return;
    while(true){
        clearScreen();
        cout<<"EXAMINER: "<<ex->name<<" ("<<examinerId<<")"<<endl<<endl;
        cout<<"1. Register New Student"<<endl;
        cout<<"2. View My Students"<<endl;
        cout<<"3. Add Questions"<<endl;
        cout<<"4. View Results"<<endl;
        cout<<"5. Export Student IDs to File"<<endl;
        cout<<"6. View Questions"<<endl;
        cout<<"7. Set MCQ Duration"<<endl;
        cout<<"8. Edit/Delete Questions"<<endl;
        cout<<"9. Back to Main Menu"<<endl;
        cout<<"Choice: ";
        int c;
        cin>>c;
        cin.ignore(1000,'\n');
        if(c==1){
            clearScreen();
            cout<<"REGISTER NEW STUDENT"<<endl<<endl;
            Student s;
            cout<<"Name: ";getline(cin,s.name);
            cout<<"Email: ";getline(cin,s.email);
            s.category=getOrCreateCategory(*ex);
            s.examinerId=examinerId;
            s.id1=generateID();
            s.id2=generateID();
            d->students.push_back(s);
            cout<<endl<<"Student Registered Successfully!"<<endl;
            cout<<"Name     : "<<s.name<<endl;
            cout<<"Category : "<<categories[s.category]<<endl;
            cout<<"ID 1     : "<<s.id1<<endl;
            cout<<"ID 2     : "<<s.id2<<endl<<endl;
            saveExaminerData(examinerId);
            pressEnter();
        }
        else if(c==2){
            clearScreen();
            cout<<"MY STUDENTS LIST"<<endl<<endl;
            if(d->students.empty()){
                cout<<"No students registered yet."<<endl;
            }else{
                for(size_t i=0;i<d->students.size();i++){
                    const Student& s=d->students[i];
                    cout<<(i+1)<<". "<<s.name<<" ("<<s.email<<")"<<endl;
                    cout<<"   Category: "<<categories[s.category]<<endl;
                    cout<<"   ID1: "<<s.id1<<(s.used1?" [USED]":"")<<endl;
                    cout<<"   ID2: "<<s.id2<<(s.used2?" [USED]":"")<<endl<<endl;
                }
            }
            pressEnter();
        }
        else if(c==3){
            clearScreen();
            cout<<"ADD NEW QUESTION"<<endl<<endl;
            int cat=getOrCreateCategory(*ex);
            if(d->questionsPerCategory[cat].size()>=50){
                cout<<"Maximum limit of 50 questions per category reached!"<<endl;
                pressEnter();
                continue;
            }
            Question q;
            cout<<"Question type (1 = MCQ, 2 = Paragraph): ";
            int t;cin>>t;cin.ignore(1000,'\n');
            q.type=t-1;
            cout<<"Question text / prompt:"<<endl;
            getline(cin,q.text);
            if(q.type==0){
                for(int i=0;i<4;++i){
                    cout<<"Option "<<i<<": ";
                    getline(cin,q.opt[i]);
                }
                cout<<"Correct option number (0-3): ";
                cin>>q.correct;cin.ignore(1000,'\n');
            }else if(q.type==1){
                cout<<"Duration for this question (minutes): ";
                cin>>q.durationMinutes;cin.ignore(1000,'\n');
            }
            d->questionsPerCategory[cat].push_back(q);
            cout<<endl<<"Question added successfully!"<<endl;
            saveExaminerData(examinerId);
            pressEnter();
        }
        else if(c==4){
            clearScreen();
            cout<<"VIEW EXAM RESULTS"<<endl<<endl;
            if(d->results.empty()){
                cout<<"No results available yet."<<endl;
            }else{
                for(size_t i=0;i<d->results.size();i++){
                    const Result& r=d->results[i];
                    cout<<(i+1)<<". "<<r.name<<" ("<<r.id<<")"<<endl;
                    cout<<"   Category      : "<<categories[r.category]<<endl;
                    cout<<"   MCQ Marks     : "<<r.mcqMarks<<"%"<<endl;
                    cout<<"   Paragraph Marks: "<<r.paragraphMarks<<endl;
                    cout<<"   Date          : "<<r.date<<endl<<endl;
                }
            }
            pressEnter();
        }
        else if(c==5){
            clearScreen();
            cout<<"EXPORT STUDENT IDs"<<endl;
            string f="students_"+examinerId+".txt";
            ofstream out(f.c_str());
            if(!out){
                cout<<"Error creating file!"<<endl;
            }else{
                for(size_t i=0;i<d->students.size();i++){
                    const Student& s=d->students[i];
                    out<<s.name<<"|"<<s.email<<"|"
                    <<s.id1<<"|"<<s.id2<<"|"
                    <<categories[s.category]<<endl;
                }
                cout<<"Exported to: "<<f<<endl;
            }
            pressEnter();
        }
        else if(c==6){
            clearScreen();
            cout<<"VIEW QUESTIONS"<<endl<<endl;
            int cat=getOrCreateCategory(*ex);
            if(d->questionsPerCategory[cat].empty()){
                cout<<"No questions available for "<<categories[cat]<<endl;
                cout<<"Would you like to load default questions? (y/n): ";
                string r;
                getline(cin,r);
                if(!r.empty()&&(r[0]=='y'||r[0]=='Y')){
                    addDefaultQuestions(cat,d->questionsPerCategory[cat]);
                    saveExaminerData(examinerId);
                    cout<<"Default questions loaded!"<<endl;
                }
            }
            vector<Question>& qs=d->questionsPerCategory[cat];
            cout<<"Questions for "<<categories[cat]<<" ("<<qs.size()<<" questions):"<<endl<<endl;
            for(size_t i=0;i<qs.size();i++){
                cout<<"Q"<<(i+1)<<". "<<qs[i].text<<endl;
                if(qs[i].type==0){
                    for(int j=0;j<4;j++){
                        cout<<"   "<<j<<") "<<qs[i].opt[j];
                        if(j==qs[i].correct)cout<<" [Correct]";
                        cout<<endl;
                    }
                }else{
                    cout<<"   [Paragraph Question]"<<endl;
                    cout<<"   Duration: "<<qs[i].durationMinutes<<" minutes"<<endl;
                }
                cout<<endl;
            }
            pressEnter();
        }
        else if(c==7){
            clearScreen();
            cout<<"SET MCQ DURATION"<<endl<<endl;
            int cat=getOrCreateCategory(*ex);
            cout<<"Current duration for "<<categories[cat]<<": "
            <<d->settingsPerCategory[cat].duration<<" minutes"<<endl;
            cout<<"Enter new duration (minutes): ";
            int dur;
            cin>>dur;
            cin.ignore(1000,'\n');
            if(dur>0){
                d->settingsPerCategory[cat].duration=dur;
                saveExaminerData(examinerId);
                cout<<"Duration updated successfully!"<<endl;
            }else{
                cout<<"Invalid duration!"<<endl;
            }
            pressEnter();
        }
        else if(c==8){
            clearScreen();
            cout<<"EDIT/DELETE QUESTIONS"<<endl<<endl;
            int cat=getOrCreateCategory(*ex);
            vector<Question>& qs=d->questionsPerCategory[cat];
            if(qs.empty()){
                cout<<"No questions available for editing."<<endl;
                pressEnter();
                continue;
            }
            cout<<"Select question to edit/delete:"<<endl;
            for(size_t i=0;i<qs.size();i++)
                cout<<(i+1)<<". "<<qs[i].text<<endl;
            cout<<"0. Back"<<endl;
            cout<<"Choice: ";
            int qc;
            cin>>qc;
            cin.ignore(1000,'\n');
            if(qc>0&&qc<=static_cast<int>(qs.size())){
                Question& q=qs[qc-1];
                cout<<endl<<"Current question: "<<q.text<<endl;
                cout<<"1. Edit Question"<<endl;
                cout<<"2. Delete Question"<<endl;
                cout<<"Choice: ";
                int a;
                cin>>a;
                cin.ignore(1000,'\n');
                if(a==1){
                    cout<<"New question text (current: "<<q.text<<"):"<<endl;
                    string nt;
                    getline(cin,nt);
                    if(!nt.empty())q.text=nt;
                    if(q.type==0){
                        for(int i=0;i<4;i++){
                            cout<<"New option "<<i<<" (current: "<<q.opt[i]<<"): ";
                            string no;
                            getline(cin,no);
                            if(!no.empty())q.opt[i]=no;
                        }
                        cout<<"New correct option (current: "<<q.correct<<"): ";
                        int nc;
                        cin>>nc;
                        cin.ignore(1000,'\n');
                        if(nc>=0&&nc<=3)q.correct=nc;
                    }else{
                        cout<<"New duration (current: "<<q.durationMinutes<<"): ";
                        int nd;
                        cin>>nd;
                        cin.ignore(1000,'\n');
                        if(nd>0)q.durationMinutes=nd;
                    }
                    cout<<"Question updated!"<<endl;
                }
                else if(a==2){
                    qs.erase(qs.begin()+(qc-1));
                    cout<<"Question deleted!"<<endl;
                }
                saveExaminerData(examinerId);
                pressEnter();
            }
        }
        else if(c==9){
            break;
        }
        else{
            cout<<"Invalid choice!"<<endl;
            pressEnter();
        }
    }
}

void CygenticTestCenter::studentExam(const string& testId){
    Student* student=nullptr;
    ExaminerData* data=nullptr;
    string examinerId;
    for(size_t i=0;i<examinerDataList.size();i++){
        for(size_t j=0;j<examinerDataList[i].students.size();j++){
            Student& s=examinerDataList[i].students[j];
            if(s.id1==testId||s.id2==testId){
                student=&s;
                data=&examinerDataList[i];
                examinerId=examinerDataList[i].examinerId;
                break;
            }
        }
        if(student)break;
    }
    if(!student||!data){
        cout<<"Error: Invalid or expired Test ID!"<<endl;
        pressEnter();
        return;
    }
    int cat=student->category;
    vector<Question>& qs=data->questionsPerCategory[cat];
    if(qs.empty()){
        cout<<"No questions available for this category yet!"<<endl;
        pressEnter();
        return;
    }
    int duration=data->settingsPerCategory[cat].duration;
    cout<<"Starting Exam - "<<categories[cat]<<endl;
    cout<<"Time limit: "<<duration<<" minutes"<<endl;
    cout<<"Total Questions: "<<qs.size()<<endl<<endl;
    pressEnter();
    int correctCount=0;
    vector<string> paraAnswers;
    for(size_t i=0;i<qs.size();i++){
        clearScreen();
        cout<<"Question "<<(i+1)<<" of "<<qs.size()<<endl;
        cout<<"================================"<<endl<<endl;
        const Question& q=qs[i];
        cout<<q.text<<endl<<endl;
        if(q.type==0){
            for(int j=0;j<4;++j)cout<<j<<") "<<q.opt[j]<<endl;
            cout<<endl<<"Your answer (0-3): ";
            int a;
            cin>>a;
            cin.ignore(1000,'\n');
            if(a>=0&&a<=3)if(a==q.correct)correctCount++;
        }
        else if(q.type==1){
            cout<<"This is a paragraph question."<<endl;
            cout<<"Suggested time: "<<q.durationMinutes<<" minutes"<<endl<<endl;
            cout<<"Write your answer below (press Enter twice to finish):"<<endl;
            cout<<"----------------------------------------------------"<<endl;
            string an,l;
            cin.ignore();
            while(true){
                getline(cin,l);
                if(l.empty())break;
                an+=l+"\n";
            }
            paraAnswers.push_back(an);
        }
        cout<<endl<<"Press Enter for next question...";
        cin.get();
    }
    int mcqCount=0;
    for(size_t i=0;i<qs.size();i++)if(qs[i].type==0)mcqCount++;
    int mcqPercent=(mcqCount>0)?(correctCount*100)/mcqCount:0;
    Result result;
    result.name=student->name;
    result.email=student->email;
    result.id=testId;
    result.date=currentTime();
    result.category=cat;
    result.mcqMarks=mcqPercent;
    result.paragraphMarks=0;
    result.paragraphAnswers=paraAnswers;
    result.examinerId=examinerId;
    data->results.push_back(result);
    clearScreen();
    cout<<"EXAM COMPLETED SUCCESSFULLY!"<<endl<<endl;
    cout<<"Name: "<<student->name<<endl;
    cout<<"Category: "<<categories[cat]<<endl;
    cout<<"MCQ Score: "<<mcqPercent<<"% ("<<correctCount<<" out of "<<mcqCount<<" correct)"<<endl;
    cout<<"Paragraph answers submitted: "<<paraAnswers.size()<<endl;
    cout<<"Paragraph answers will be evaluated by examiner."<<endl;
    cout<<"Thank you for participating!"<<endl<<endl;
    pressEnter();
}

int main(){
    CygenticTestCenter center;
    center.run();
    return 0;
}
