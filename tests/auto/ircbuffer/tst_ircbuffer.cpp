/*
 * Copyright (C) 2008-2013 The Communi Project
 *
 * This test is free, and not covered by the LGPL license. There is no
 * restriction applied to their modification, redistribution, using and so on.
 * You can study them, modify them, use them in your own program - either
 * completely or partially.
 */

#include "ircbuffer.h"
#include <QtTest/QtTest>

class tst_IrcBuffer : public QObject
{
    Q_OBJECT

private slots:
    void testDefaults();
    void testTitleNamePrefix();
    void testSticky();
    void testPersistent();
};

void tst_IrcBuffer::testDefaults()
{
    IrcBuffer buffer;
    QVERIFY(buffer.title().isEmpty());
    QVERIFY(buffer.name().isEmpty());
    QVERIFY(buffer.prefix().isEmpty());
    QVERIFY(!buffer.isChannel());
    QVERIFY(!buffer.toChannel());
    QVERIFY(!buffer.connection());
    QVERIFY(!buffer.network());
    QVERIFY(!buffer.model());
    QVERIFY(!buffer.isActive());
    QVERIFY(!buffer.isSticky());
    QVERIFY(!buffer.isPersistent());
}

void tst_IrcBuffer::testTitleNamePrefix()
{
    IrcBuffer buffer;

    QSignalSpy titleSpy(&buffer, SIGNAL(titleChanged(QString)));
    QSignalSpy nameSpy(&buffer, SIGNAL(nameChanged(QString)));
    QSignalSpy prefixSpy(&buffer, SIGNAL(prefixChanged(QString)));
    QVERIFY(titleSpy.isValid());
    QVERIFY(nameSpy.isValid());
    QVERIFY(prefixSpy.isValid());

    buffer.setName("name");
    QCOMPARE(buffer.title(), QString("name"));
    QCOMPARE(buffer.name(), QString("name"));
    QCOMPARE(buffer.prefix(), QString());
    QCOMPARE(titleSpy.count(), 1);
    QCOMPARE(titleSpy.last().first().toString(), QString("name"));
    QCOMPARE(nameSpy.count(), 1);
    QCOMPARE(nameSpy.last().first().toString(), QString("name"));
    QCOMPARE(prefixSpy.count(), 0);

    buffer.setPrefix("prefix");
    QCOMPARE(buffer.title(), QString("prefixname"));
    QCOMPARE(buffer.name(), QString("name"));
    QCOMPARE(buffer.prefix(), QString("prefix"));
    QCOMPARE(titleSpy.count(), 2);
    QCOMPARE(titleSpy.last().first().toString(), QString("prefixname"));
    QCOMPARE(nameSpy.count(), 1);
    QCOMPARE(prefixSpy.count(), 1);
    QCOMPARE(prefixSpy.last().first().toString(), QString("prefix"));
}

void tst_IrcBuffer::testSticky()
{
    IrcBuffer buffer;
    QVERIFY(!buffer.isSticky());

    QSignalSpy spy(&buffer, SIGNAL(stickyChanged(bool)));
    QVERIFY(spy.isValid());

    buffer.setSticky(true);
    QVERIFY(buffer.isSticky());
    QCOMPARE(spy.count(), 1);
    QVERIFY(spy.last().last().toBool());

    buffer.setSticky(false);
    QVERIFY(!buffer.isSticky());
    QCOMPARE(spy.count(), 2);
    QVERIFY(!spy.last().last().toBool());
}

void tst_IrcBuffer::testPersistent()
{
    IrcBuffer buffer;
    QVERIFY(!buffer.isPersistent());

    QSignalSpy spy(&buffer, SIGNAL(persistentChanged(bool)));
    QVERIFY(spy.isValid());

    buffer.setPersistent(true);
    QVERIFY(buffer.isPersistent());
    QCOMPARE(spy.count(), 1);
    QVERIFY(spy.last().last().toBool());

    buffer.setPersistent(false);
    QVERIFY(!buffer.isPersistent());
    QCOMPARE(spy.count(), 2);
    QVERIFY(!spy.last().last().toBool());
}

QTEST_MAIN(tst_IrcBuffer)

#include "tst_ircbuffer.moc"