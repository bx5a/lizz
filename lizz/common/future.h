#ifndef LIZZ_COMMON_FUTURE_H_
#define LIZZ_COMMON_FUTURE_H_

#include <system_error>
#include <memory>

namespace lizz {
  
// Interface
namespace priv {
    
template <class T>
class Future {
 public:
  virtual void Wait() = 0;
  virtual T Get() = 0;
  virtual std::error_code GetError() = 0;
};
  
template <class T>
using ResultType = typename std::result_of<decltype(&T::get)(T)>::type;
  
}  // namespace priv
  

// Indirection to acces member through Object instead of pointer
template <class T>
class Future {
public:
  Future(std::shared_ptr<priv::Future<T>> p_future) : p_future_(p_future) {}
  void Wait() { p_future_->Wait(); }
  T Get() { return p_future_->Get(); }
  std::error_code GetError() { return p_future_->GetError(); }
  
private:
  std::shared_ptr<priv::Future<T>> p_future_;
};
  
// Define a "generic" future. That works for both std::future and casablanca's
// pplx::task
template <class T>
class GenericFuture : public priv::Future<priv::ResultType<T>> {
 public:
  GenericFuture(std::shared_ptr<T> p_future_t) :
    p_future_t_(p_future_t), is_init_(false) {}
  
  GenericFuture(
      std::function<std::shared_ptr<T>(std::error_code&)> create_future) {
    p_future_t_ = create_future(ref(err_));
  }
  
  void Wait() {
    p_future_t_->wait();
  }
  
  priv::ResultType<T> Get() {
    try {
      // TODO(bx5a): search the doc why you can't do std::future.get() several
      // times
      if (!is_init_) {
        output_ = p_future_t_->get();
      }
      is_init_ = true;
      return output_;
    } catch (const std::exception& e) {
      // TODO(bx5a): create a more explicit error
      // TODO(bx5a): maybe Get should return an error instead of reporting it
      // through class error
      err_ = std::make_error_code(std::errc::interrupted);
    }
    return priv::ResultType<T>();
  }
  
  std::error_code GetError() {
    return err_;
  }
  
 private:
  std::shared_ptr<T> p_future_t_;
  priv::ResultType<T> output_;
  bool is_init_;
  std::error_code err_;
};
  
}  // namespace lizz

#endif  // LIZZ_COMMON_FUTURE_H_
