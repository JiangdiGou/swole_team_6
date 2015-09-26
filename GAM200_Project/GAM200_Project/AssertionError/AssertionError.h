//author Nolan Yoo

class AssertionError : public std::exception
{
public:
  AssertionError(std::string m="Unknown AssertionError!") : msg(m) {}
  //AssertionError() throw() {}
  const char* what() const throw() { return msg.c_str(); }

private:
  std::string msg;
};