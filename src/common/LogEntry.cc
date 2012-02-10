
#include "LogEntry.h"
#include "Formatter.h"

void LogEntryKey::encode(bufferlist& bl) const
{
  ::encode(who, bl);
  ::encode(stamp, bl);
  ::encode(seq, bl);
}

void LogEntryKey::decode(bufferlist::iterator& bl)
{
  ::decode(who, bl);
  ::decode(stamp, bl);
  ::decode(seq, bl);
}

void LogEntryKey::dump(Formatter *f) const
{
  f->dump_stream("who") << who;
  f->dump_stream("stamp") << stamp;
  f->dump_unsigned("seq", seq);
}

void LogEntryKey::generate_test_instances(list<LogEntryKey*>& o)
{
  o.push_back(new LogEntryKey);
  o.push_back(new LogEntryKey(entity_inst_t(), utime_t(1,2), 34));
}

// ----

void LogEntry::encode(bufferlist& bl) const
{
  __u8 v = 1;
  ::encode(v, bl);
  __u16 t = type;
  ::encode(who, bl);
  ::encode(stamp, bl);
  ::encode(seq, bl);
  ::encode(t, bl);
  ::encode(msg, bl);
}

void LogEntry::decode(bufferlist::iterator& bl)
{
  __u8 v;
  ::decode(v, bl);
  __u16 t;
  ::decode(who, bl);
  ::decode(stamp, bl);
  ::decode(seq, bl);
  ::decode(t, bl);
  type = (clog_type)t;
  ::decode(msg, bl);
}

void LogEntry::dump(Formatter *f) const
{
  f->dump_stream("who") << who;
  f->dump_stream("stamp") << stamp;
  f->dump_unsigned("seq", seq);
  f->dump_stream("type") << type;
  f->dump_string("message", msg);
}

void LogEntry::generate_test_instances(list<LogEntry*>& o)
{
  o.push_back(new LogEntry);
}


// -----

void LogSummary::encode(bufferlist& bl) const
{
  __u8 v = 1;
  ::encode(v, bl);
  ::encode(version, bl);
  ::encode(tail, bl);
}

void LogSummary::decode(bufferlist::iterator& bl)
{
  __u8 v;
  ::decode(v, bl);
  ::decode(version, bl);
  ::decode(tail, bl);
}

void LogSummary::dump(Formatter *f) const
{
  f->dump_unsigned("version", version);
  f->open_array_section("tail");
  for (list<LogEntry>::const_iterator p = tail.begin(); p != tail.end(); ++p) {
    f->open_object_section("entry");
    p->dump(f);
    f->close_section();
  }
  f->close_section();
}

void LogSummary::generate_test_instances(list<LogSummary*>& o)
{
  o.push_back(new LogSummary);
  // more!
}
