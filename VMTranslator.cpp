# include <bits/stdc++.h>
# define sf(x) s.find(x)

using namespace std;

void FindFileName(string * fname) 
{
  auto it = fname - > find(".");
  fname - > erase(it);
}

string parser(string s)
{
  string p = s;
  p.erase(remove_if(p.begin(), p.end(), ::isspace), p.end());
  auto it = p.find("//");
  auto end = p.length();
  string t;
  if (it == string::npos)
    return p;
  else if (it != string::npos) 
  {
    p.erase(it, end);
    return p;
  }
}

int retInsType(string s)
{
  if (s.size() == 0)
    return 0;
  if ((sf("add") == 0) || (sf("sub") == 0) || (sf("and") == 0) || (sf("or") == 0) || (sf("not") == 0) || (sf("neg") == 0) || (sf("eq") == 0) || (sf("gt") == 0) || (sf("lt") == 0))
    return 1;
  if ((sf("push") == 0) || (sf("pop") == 0))
    return 2;
  return 0;
}

int strtonum(string s, int start)
{
  int ans = 0, t = 1;
  for (int i = s.size() - 1; i >= start; i--)
  {
    ans += (s[i] - 48) * t;
    t *= 10;
  }
  return ans;
}

void push(string s, ofstream & f2)
{
  int id;
  if (sf("constant") == 4)
  {
    id = strtonum(s, 11);
    f2 << "@" << id << "\n" << "D=A\n" << "@SP\nAM=M+1\nA=A-1\nM=D\n";
  } 
  else if (sf("local") == 4) 
  {
    id = strtonum(s, 8);
    f2 << "@LCL\nD=M\n" << "@" << id << "\n" << "A=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
  } 
  else if (sf("argument") == 4) 
  {
    id = strtonum(s, 11);
    f2 << "@ARG\nD=M\n" << "@" << id << "\n" << "A=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
  } 
  else if (sf("pointer") == 4) 
  {
    id = strtonum(s, 11);
    if (id == 0)
      f2 << "@R3\nA=M\nD=M\n" << "@SP\nAM=M+1\nA=A-1\nM=D\n";
    else
      f2 << "@R4\nA=M\nD=M\n" << "@SP\nAM=M+1\nA=A-1\nM=D\n";
  }
}

void pop(string s, ofstream & f2)
{
  int id;
  if (sf("local") == 3) 
  {
    id = strtonum(s, 8);
    f2 << "@LCL\nD=M\n@" << id << "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
  } 
  else if (sf("argument") == 3) 
  {
    id = strtonum(s, 11);
    f2 << "@ARG\nD=M\n@" << id << "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
  } 
  else if (sf("this") == 3) 
    f2 << "@SP\nAM=M-1\nD=M\n@R3\nA=M\nM=D\n";
  else if (sf("that") == 3) 
    f2 << "@SP\nAM=M-1\nD=M\n@R4\nA=M\nM=D\n";
}

int main(int argc, char * argv[])
{
  string fname(argv[1]);
  FindFileName( & fname);
  ifstream f1((fname + ".vm").c_str());
  ofstream f2((fname + ".asm").c_str());
  string s, l, out;
  int InsType, id;
  char eq = 'a', gt = 'a', lt = 'a';
  while (getline(f1, l)) 
  {
    s = parser(l);
    InsType = retInsType(s);
    switch (TnsType) 
    {
      case 1:
      {
        if ((sf("add") == 0)) 
        {
          f2 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "A=A-1\n" << "M=D+M\n";
          break;
        } 
        else if ((sf("sub") == 0)) 
        {
          f2 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "A=A-1\n" << "M=M-D\n";
          break;
        } 
        else if ((sf("and") == 0)) 
        {
          f2 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "A=A-1\n" << "M=D&M\n";
          break;
        } 
        else if ((sf("or") == 0)) 
        {
          f2 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "A=A-1\n" << "M=D|M\n";
          break;
        } 
        else if ((sf("neg") == 0)) 
        {
          f2 << "@SP\n" << "A=M-1\n" << "M=-M\n";
          break;
        } 
        else if ((sf("not") == 0)) 
        {
          f2 << "@SP\n" << "A=M-1\n" << "M=!M\n";
          break;
        } 
        else if ((sf("gt") == 0)) 
        {
          f2 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "A=A-1\n" << "D=M-D\n" << "M=-1\n" << "@gt" << gt << "\n" << "D;JGT\n" << "@SP\n" << "A=M-1\n" << "M=0\n" << "(gt" << gt << ")\n";
          gt++;
          break;
        } 
        else if ((sf("eq") == 0)) 
        {
          f2 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "A=A-1\n" << "D=M-D\n" << "M=-1\n" << "@eq" << eq << "\n" << "D;JEQ\n" << "@SP\n" << "A=M-1\n" << "M=0\n" << "(eq" << eq << ")\n";
          eq++;
          break;
        } 
        else if ((sf("lt") == 0)) 
        {
          f2 << "@SP\n" << "AM=M-1\n" << "D=M\n" << "A=A-1\n" << "D=M-D\n" << "M=-1\n" << "@lt" << lt << "\n" << "D;JLT\n" << "@SP\n" << "A=M-1\n" << "M=0\n" << "(lt" << lt << ")\n";
          lt++;
          break;
        }
        break;
      }
      case 2:
      {
        if (sf("push") == 0) 
        {
          if (sf("constant") == 4) 
          {
            id = strtonum(s, 12);
            f2 << "@" << id << "\n" << "D=A\n" << "@SP\nAM=M+1\nA=A-1\nM=D\n";
          } 
          else if (sf("local") == 4) 
          {
            id = strtonum(s, 9);
            f2 << "@LCL\nD=M\n" << "@" << id << "\n" << "A=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
          } 
          else if (sf("argument") == 4) 
          {
            id = strtonum(s, 12);
            f2 << "@ARG\nD=M\n" << "@" << id << "\n" << "A=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
          } 
          else if (sf("pointer") == 4) 
          {
            id = strtonum(s, 11);
            if (id == 0)
              f2 << "@R3\nD=M\n" << "@SP\nAM=M+1\nA=A-1\nM=D\n";
            else
              f2 << "@R4\nD=M\n" << "@SP\nAM=M+1\nA=A-1\nM=D\n";
          } 
          else if ((sf("this") == 4)) 
          {
            id = strtonum(s, 8);
            f2 << "@R3\nD=M\n" << "@" << id << "\n" << "A=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
          } 
          else if ((sf("that") == 4)) 
          {
            id = strtonum(s, 8);
            f2 << "@R4\nD=M\n" << "@" << id << "\n" << "A=D+A\nD=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
          } 
          else if (sf("static") == 4) 
          {
            id = strtonum(s, 10);
            f2 << "@" << fname << id << "\n" << "D=M\n@SP\nAM=M+1\nA=A-1\nM=D\n";
          }
          else if (sf("temp") == 4) 
          {
            id = strtonum(s, 8);
            f2 << "@" << 5 + id << "\nD=M\n" << "@SP\nAM=M+1\nA=A-1\nM=D\n";
          }
        } 
        else if (sf("pop") == 0) 
        {
          cout << "\nPop is called\n";
          if (sf("pointer") == 3) 
          {
            id = strtonum(s, 10);
            if (id == 0)
              f2 << "@SP\nAM=M-1\nD=M\n" << "@R3\nM=D\n";
            else
              f2 << "@SP\nAM=M-1\nD=M\n" << "@R4\nM=D\n";
          }
          else if (sf("local") == 3) 
          {
            id = strtonum(s, 8);
            f2 << "@LCL\nD=M\n@" << id << "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
          } 
          else if (sf("argument") == 3) 
          {
            id = strtonum(s, 11);
            f2 << "@ARG\nD=M\n@" << id << "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
          } 
          else if (sf("this") == 3) 
          {
            id = strtonum(s, 7);
            f2 << "@R3\nD=M\n@" << id << "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
          } 
          else if (sf("that") == 3) 
          {
            id = strtonum(s, 7);
            f2 << "@R4\nD=M\n@" << id << "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
          } 
          else if (sf("static") == 3) 
          {
            id = strtonum(s, 9);
            f2 << "@" << fname << id << "\nD=A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
          } 
          else if (sf("temp") == 3) 
          {
            id = strtonum(s, 7);
            f2 << "@5\nD=A\n@" << id << "\nD=D+A\n@R13\nM=D\n@SP\nAM=M-1\nD=M\n@R13\nA=M\nM=D\n";
          }	
        }
        break;
      }
    }
  }
  f2 << "(END)\n@END\n0;JMP\n";
  f1.close();
  f2.close();
  return 0;
}