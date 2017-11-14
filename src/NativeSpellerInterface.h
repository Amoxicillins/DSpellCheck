#pragma once

#include "SpellerInterface.h"
#include <atlbase.h>

struct ISpellCheckerFactory;
struct ISpellChecker;
struct IEnumSpellingError;

class NativeSpellerInterface : public SpellerInterface
{
public:
    void init (); // init should be done after initialization, not after construction
    NativeSpellerInterface ();
    void set_language(const wchar_t* lang) override;
    bool check_word(const wchar_t* word) override;
    void add_to_dictionary(const wchar_t* word) override;
    void ignore_all(const wchar_t* word) override;
    bool is_working() const override;
    std::vector<LanguageInfo> get_language_list() const override;
    void set_multiple_languages(const std::vector<std::wstring>& list) override;
    std::vector<std::wstring> get_suggestions(const wchar_t* word) override;
    void cleanup();

private:
    void test();
    void init_impl();
private:
    struct ptrs
    {
    CComPtr<ISpellCheckerFactory> m_factory;
    CComPtr<ISpellChecker> m_speller;
    CComPtr<IEnumSpellingError> m_err;
    };
    std::unique_ptr<ptrs> m_ptrs;
    bool m_ok = false;
    bool m_com_initialized = true;
};