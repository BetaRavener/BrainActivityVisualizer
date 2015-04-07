#include <cassert>

template <typename T>
SafePtr<T>::SafePtr(){
	
}

template <typename T>
SafePtr<T>::SafePtr(const std::shared_ptr<T>& shared){
	std::weak_ptr<T>::operator=(shared);
}

template <typename T>
T* SafePtr<T>::operator->(){
        //assert(!this->expired());
	return this->lock().get();
}

template <typename T>
T& SafePtr<T>::operator*(){
        //assert(!this->expired());
	return *this->lock();
}

template <typename T>
SafePtr<T>& SafePtr<T>::operator=(const std::shared_ptr<T>& shared){
        std::weak_ptr<T>::operator=(shared);
	return *this;
}

template <typename T>
SafePtr<T>::operator bool(){
	return !this->expired();
}
