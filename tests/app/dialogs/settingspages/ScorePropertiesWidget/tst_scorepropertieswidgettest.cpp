/**
 * @author  Thomas Baumann <teebaum@ymail.com>
 *
 * @section LICENSE
 * Licensed under the GNU GENERAL PUBLIC LICENSE. See LICENSE for details.
 *
 */

#include <QString>
#include <QtTest>
#include <QSignalSpy>
#include <QFont>
#include <QColor>
#include <app/dialogs/settingspages/scorepropertieswidget.h>
#include "ui_scorepropertieswidget.h"

class ScorePropertiesWidgetTest : public QObject
{
    Q_OBJECT

public:
    ScorePropertiesWidgetTest();

private Q_SLOTS:
    void init();
    void cleanup();
    void testConstructor();
    void testSetText();
    void testSetWidgetEnabled();
    void testSetAlignment();
    void testSetRow();
    void testSetFont();
    void testSetColor();
    void testSetPositionIsInUseMessage();

private:
    void checkWidgetEnabled(bool enabled);
    ScorePropertiesWidget *m_scorePropertiesWidget;
    Ui::ScorePropertiesWidget *m_widgetUi;
};

ScorePropertiesWidgetTest::ScorePropertiesWidgetTest()
    : m_scorePropertiesWidget(0),
      m_widgetUi(0)
{
}

void ScorePropertiesWidgetTest::init()
{
    m_scorePropertiesWidget = new ScorePropertiesWidget();
    m_widgetUi = m_scorePropertiesWidget->ui;
}

void ScorePropertiesWidgetTest::cleanup()
{
    delete m_scorePropertiesWidget;
}

void ScorePropertiesWidgetTest::testConstructor()
{
    QVERIFY2(m_widgetUi->alignmentComboBox->findText("Left") != -1,
             "Missing option in combobox");
    QVERIFY2(m_widgetUi->alignmentComboBox->findText("Right") != -1,
             "Missing option in combobox");
    QVERIFY2(m_widgetUi->alignmentComboBox->findText("Center") != -1,
             "Missing option in combobox");
    QVERIFY2(m_widgetUi->enabledCheckBox->isChecked() == false,
             "Enabled checkbox is checked by default");

    checkWidgetEnabled(false);
}

void ScorePropertiesWidgetTest::testSetText()
{
    QString testText("dkieuznfvngjdh 2345ndsjksd");
    m_scorePropertiesWidget->setText(testText);
    QVERIFY2(m_widgetUi->textLabel->text() == testText,
             "Text wasn't set");
}

void ScorePropertiesWidgetTest::testSetWidgetEnabled()
{
    QSignalSpy spy(m_scorePropertiesWidget, SIGNAL(enabledChanged(bool)));
    QVERIFY2(m_scorePropertiesWidget->isWidgetEnabled() == false,
             "Widget is enabled by default");

    m_scorePropertiesWidget->setWidgetEnabled(true);
    QVERIFY2(spy.count() == 0, "Enabled changed must only be emitted when changed through Ui");
    QVERIFY2(m_scorePropertiesWidget->isWidgetEnabled() == true,
             "Enabled couldn't be set");
    QVERIFY2(m_widgetUi->enabledCheckBox->isChecked(),
             "Checkbox wasn't set checked in ui");
    checkWidgetEnabled(true);

    m_widgetUi->enabledCheckBox->setChecked(false);
    QVERIFY2(spy.count() == 1, "enabled changed wasn't emitted when changed through ui");
}

void ScorePropertiesWidgetTest::testSetAlignment()
{
    QSignalSpy spy(m_scorePropertiesWidget, SIGNAL(alignmentChanged(Settings::TextAlignment)));
    Settings::TextAlignment testAlignment = Settings::TextAlignment::Center;
    Settings::TextAlignment testAlignmentThroughUi = Settings::TextAlignment::Left;

    QVERIFY2(m_scorePropertiesWidget->alignment() == Settings::TextAlignment::NoAlignment,
             "There must be no alignment per default");
    m_scorePropertiesWidget->setAlignment(testAlignment);
    QVERIFY2(spy.count() == 0, "Alignment changed signal must only be emitted when changed through ui");
    QVERIFY2(m_scorePropertiesWidget->alignment() == testAlignment,
             "Alignment wasn't set");
    Settings::TextAlignment uiAlignmentValue = m_widgetUi->alignmentComboBox->currentData().value<Settings::TextAlignment>();
    QVERIFY2(uiAlignmentValue == testAlignment, "Alignment wasn't set in ui");

    int testDataIndex = m_widgetUi->alignmentComboBox->findData(QVariant::fromValue<Settings::TextAlignment>(testAlignmentThroughUi));
    QVERIFY2(testDataIndex != -1, "Test data can't be found in combo box");
    m_widgetUi->alignmentComboBox->setCurrentIndex(testDataIndex);
    QVERIFY2(spy.count() == 1, "Alignment changed wasn't emitted when changed through ui");
}

void ScorePropertiesWidgetTest::testSetRow()
{
    QSignalSpy spy(m_scorePropertiesWidget, SIGNAL(rowChanged(int)));
    int testRow = 3;
    int testRowThroughUi = 2;
    Q_ASSERT(m_widgetUi->rowSpinBox->maximum() >= testRow);

    QVERIFY2(m_widgetUi->rowSpinBox->minimum() == 1, "Wrong minumum row in ui");
    QVERIFY2(m_scorePropertiesWidget->row() == 0, "Wrong default row");
    m_scorePropertiesWidget->setRow(testRow);
    QVERIFY2(spy.count() == 0, "Row changed signal must only be emitted when changed through ui");
    QVERIFY2(m_scorePropertiesWidget->row() == testRow, "Row wasn't set");
    int uiRow = m_widgetUi->rowSpinBox->value();
    QVERIFY2(uiRow == testRow, "Row wasn't set in ui");

    m_widgetUi->rowSpinBox->setValue(testRowThroughUi);
    QVERIFY2(spy.count() == 1, "Row changed wasn't emitted when changed through ui");
}

void ScorePropertiesWidgetTest::testSetFont()
{
    QSignalSpy spy(m_scorePropertiesWidget, SIGNAL(fontChanged(QFont)));
    QFont testFont = QFont("Lucida Console", 56, QFont::SemiCondensed, true);
    Q_ASSERT(m_scorePropertiesWidget->font() != testFont);

    m_scorePropertiesWidget->setFont(testFont);
    QVERIFY2(spy.count() == 0, "Font changed signal must only be emitted when changed through ui");
    QVERIFY2(m_scorePropertiesWidget->font() == testFont, "Font wasn't set");
}

void ScorePropertiesWidgetTest::testSetColor()
{
    QSignalSpy spy(m_scorePropertiesWidget, SIGNAL(colorChanged(QColor)));
    QColor testColor = QColor("#236395");
    Q_ASSERT(m_scorePropertiesWidget->color() != testColor);

    m_scorePropertiesWidget->setColor(testColor);
    QVERIFY2(spy.count() == 0, "Color changed signal must only be emitted when changed through ui");
    QVERIFY2(m_scorePropertiesWidget->color() == testColor, "Color wasn't set");
}

void ScorePropertiesWidgetTest::testSetPositionIsInUseMessage()
{
    QVERIFY2(m_widgetUi->positionIsInUseLabel->text().isEmpty(),
             "Position in use message must be empty per default");

    m_scorePropertiesWidget->setPositionIsInUseMessage(true);

    QVERIFY2(m_widgetUi->positionIsInUseLabel->text().isEmpty() == false,
             "Position is in use message wasn't set");

    m_scorePropertiesWidget->setPositionIsInUseMessage(false);

    QVERIFY2(m_widgetUi->positionIsInUseLabel->text().isEmpty() == true,
             "Position is in use message wasn't cleared");
    QVERIFY2(m_scorePropertiesWidget->isPositionInUseMessageActive() == false,
             "Position is in use message isn't set to false");
}

void ScorePropertiesWidgetTest::checkWidgetEnabled(bool enabled)
{
    QVERIFY2(m_widgetUi->enabledCheckBox->isEnabled(),
             "CheckBox has always be enabled");
    QVERIFY2(m_widgetUi->textLabel->isEnabled() == enabled,
             "Widget has wrong enabled state");
    QVERIFY2(m_widgetUi->rowLabel->isEnabled() == enabled,
             "Widget has wrong enabled state");
    QVERIFY2(m_widgetUi->rowSpinBox->isEnabled() == enabled,
             "Widget has wrong enabled state");
    QVERIFY2(m_widgetUi->alignmentLabel->isEnabled() == enabled,
             "Widget has wrong enabled state");
    QVERIFY2(m_widgetUi->alignmentComboBox->isEnabled() == enabled,
             "Widget has wrong enabled state");
    QVERIFY2(m_widgetUi->fontPushButton->isEnabled() == enabled,
             "Widget has wrong enabled state");
    QVERIFY2(m_widgetUi->colorPushButton->isEnabled() == enabled,
             "Widget has wrong enabled state");
    QVERIFY2(m_widgetUi->positionIsInUseLabel->isEnabled() == enabled,
             "Widget has wrong enabled state");
}

QTEST_MAIN(ScorePropertiesWidgetTest)

#include "tst_scorepropertieswidgettest.moc"
