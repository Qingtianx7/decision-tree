#ifndef GBOOST_CONFIG_H_
#define GBOOST_CONFIG_H_
/**
 * \file gboost_config.h
 * \brief helper class to load in configures from file
 */
#define CRT_SECURE_NO_WARNINGS
#include <string>
#include "utils/gboost_utils.h" // Assert

namespace gboost {
namespace utils {
/**
 * \brief an iterator that iterates over a configure file and gets the configures
 */
class ConfigIterator{
 public:
  /**
   * \brief constructor
   * \param fname name of configure file
   */
  ConfigIterator(const char *fname) {}
  /** \brief destructor */
  ~ConfigIterator() {}
  /**
   * \brief get current name, called after Next returns true
   * \return current parameter name
   */
  inline const char *name(void)const {}
  /**
   * \brief get current value, called after Next returns true
   * \return current parameter value
   */
  inline const char *val(void)const {}
  /**
   * \brief move iterator to next position
   * \return true if there is value in next position
   */
  inline bool Next(void) {}
};
}


namespace utils {
/**
 * \brief a class that save parameter configurations
 *        temporally and allows to get them out later
 *        there are two kinds of priority in ConfigSaver
 */
class ConfigSaver{
 private:
  std::vector<std::string> names;
  std::vector<std::string> values;
  std::vector<std::string> names_high;
  std::vector<std::string> values_high;
  size_t idx;
 public:
  /** \brief constructor */
  ConfigSaver(void) { idx = 0; }
  /** \brief clear all saves */
  inline void Clear (void) {
    idx = 0;
    names.clear(); values.clear();
    names_high.clear(); values_high.clear();
  }
  /**
   * \brief push back a parameter setting
   * \param name: name of parameter
   * \param val:  value of parameter
   * \param priority: whether the setting has higher priority: high priority occurs
   *        latter when read from ConfigSaver, and overwriter existing settings
   */
  inline void PushBack(const char *name, const char *val, int priority = 0) {
    if(priority == 0) {
      names.push_back(std::string(name));
      values.push_back(std::string(val));
    } else {
      names_high.push_back( std::string(name));
      values_high.push_back( std::string(val));
    }
  }
  /** \brief set pointer to beginning of the ConfigSaver */
  inline void BeforeFirst( void ){
    idx = 0;
  }
  /**
   * \brief move iterator to next position
   * \return true if there is value in Next position
   */
  inline bool Next( void ){
    if( idx >= names.size() + names_high.size() ){
      return false;
    }
    idx ++;
    return true;
  }
  /**
   * \brief get current name, called after Next returns true
   * \return current parameter name
   */
  inline const char *name( void )const{
    Assert( idx > 0, "can't call name before first");
    size_t i = idx - 1;
    if( i >= names.size() ){
      return names_high[ i - names.size() ].c_str();
    }else{
      return names[ i ].c_str();
    }
  }
  /**
   * \brief get current value, called after Next returns true
   * \return current parameter value
   */
  inline const char *val( void )const{
    Assert( idx > 0, "can't call name before first");
    size_t i = idx - 1;
    if( i >= values.size() ){
      return values_high[ i - values.size() ].c_str();
    }else{
      return values[ i ].c_str();
    }
  }
};
}
}
#endif
