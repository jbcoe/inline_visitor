// FIXME: Add header info

#ifndef INLINE_VISITOR_INLINE_VISITOR_H
#define INLINE_VISITOR_INLINE_VISITOR_H

template <typename T, typename F, typename BaseInnerVisitor, typename ArgsT>
class ComposeVisitor
{
public:
  class InnerVisitor : public BaseInnerVisitor
  {
  public:
    using BaseInnerVisitor::Visit;
    typedef typename BaseInnerVisitor::VisitorInterface VisitorInterface;

    InnerVisitor(ArgsT&& args)
        : BaseInnerVisitor(std::move(args.second)), m_f(std::move(args.first))
    {
    }

    void Visit(T& t) final
    {
      VisitImpl(t);
    }

  private:
    template <typename F_ = F>
    typename std::enable_if<
        std::is_assignable<std::function<void(T&)>, F_>::value>::type
    VisitImpl(T& t)
    {
      m_f(t);
    }


    template <typename F_ = F>
    typename std::enable_if<std::is_assignable<
        std::function<void(T&, VisitorInterface&)>, F_>::value>::type
    VisitImpl(T& t)
    {
      m_f(t, *this);
    }

    F m_f;
  };

  ComposeVisitor(ArgsT&& args) : m_args(std::move(args))
  {
  }

  template <typename Tadd, typename Fadd>
  ComposeVisitor<Tadd, Fadd, InnerVisitor, std::pair<Fadd, ArgsT>>
  on(Fadd&& f) &&
  {
    return ComposeVisitor<Tadd, Fadd, InnerVisitor, std::pair<Fadd, ArgsT>>(
        std::make_pair(std::move(f), std::move(m_args)));
  }

  template <typename InnerVisitor_ = InnerVisitor>
  typename std::enable_if<!std::is_abstract<InnerVisitor_>::value,
                          InnerVisitor>::type
  end_visitor() &&
  {
    return InnerVisitor(std::move(m_args));
  }

  ArgsT m_args;
};


template <typename TVisitorBase>
class EmptyVisitor
{
public:
  class InnerVisitor : public TVisitorBase
  {
  public:
    using TVisitorBase::Visit;
    typedef TVisitorBase VisitorInterface;
    InnerVisitor(std::nullptr_t)
    {
    }
  };

  template <typename Tadd, typename Fadd>
  ComposeVisitor<Tadd, Fadd, InnerVisitor, std::pair<Fadd, std::nullptr_t>>
  on(Fadd&& f) &&
  {
    return ComposeVisitor<Tadd, Fadd, InnerVisitor,
                          std::pair<Fadd, std::nullptr_t>>(
        std::make_pair(std::move(f), nullptr));
  }
};


template <typename TVisitorBase>
EmptyVisitor<TVisitorBase> begin_visitor()
{
  return EmptyVisitor<TVisitorBase>();
}

#endif // INLINE_VISITOR_INLINE_VISITOR_H
