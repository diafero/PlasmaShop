#include "OptionsDialog.h"
#include <QCompleter>
#include <QDirModel>
#include <QGridLayout>
#include <QSpacerItem>
#include <QTabWidget>
#include <QLabel>
#include <QDialogButtonBox>
#include <QSettings>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QIntValidator>
#include <QToolButton>
#include <QPushButton>
#include <QFileDialog>
#include <QFontDialog>

OptionsDialog::OptionsDialog(QWidget* parent)
             : QDialog(parent)
{
    QTabWidget* tabs = new QTabWidget(this);
    QDirModel* dirModel = new QDirModel(QStringList("*"),
                                        QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Executable,
                                        QDir::Name | QDir::DirsLast | QDir::IgnoreCase,
                                        this);

    // "General" (programs) tab
    QWidget* tabProgs = new QWidget(tabs);
    fPrpEditorPath = new QLineEdit(tabProgs);
    fPrpEditorPath->setCompleter(new QCompleter(dirModel, fPrpEditorPath));
    QToolButton* browsePrpEditor = new QToolButton(tabProgs);
    browsePrpEditor->setText("...");
    fVaultEditorPath = new QLineEdit(tabProgs);
    fVaultEditorPath->setCompleter(new QCompleter(dirModel, fVaultEditorPath));
    QToolButton* browseVaultEditor = new QToolButton(tabProgs);
    browseVaultEditor->setText("...");

    QGridLayout* layProgs = new QGridLayout(tabProgs);
    layProgs->setContentsMargins(8, 8, 8, 8);
    layProgs->addItem(new QSpacerItem(16, 0, QSizePolicy::Maximum, QSizePolicy::Minimum), 1, 0);
    layProgs->addWidget(new QLabel(tr("PRP Editor:"), tabProgs), 0, 0, 1, 3);
    layProgs->addWidget(fPrpEditorPath, 1, 1);
    layProgs->addWidget(browsePrpEditor, 1, 2);
    layProgs->addItem(new QSpacerItem(0, 8, QSizePolicy::Minimum, QSizePolicy::Minimum), 2, 0, 1, 3);
    layProgs->addWidget(new QLabel(tr("Vault Editor:"), tabProgs), 3, 0, 1, 3);
    layProgs->addWidget(fVaultEditorPath, 4, 1);
    layProgs->addWidget(browseVaultEditor, 4, 2);
    layProgs->addItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding), 5, 0, 1, 3);
    tabs->addTab(tabProgs, tr("General"));

    // Editor (Scintilla) tab
    QWidget* tabEditor = new QWidget(tabs);
    fSciMargin = new QCheckBox(tr("Show margins"), tabEditor);
    fSciFolding = new QCheckBox(tr("Code folding"), tabEditor);
    fSciLineNumbers = new QCheckBox(tr("Line numbers"), tabEditor);
    fSciUseSpaces = new QCheckBox(tr("Use spaces instead of tabs"), tabEditor);
    fSciAutoIndent = new QCheckBox(tr("Auto-indent"), tabEditor);
    fSciFont = new QPushButton(tr("Editor Font"), tabEditor);
    fSciIndentGuides = new QCheckBox(tr("Show indentation guides"), tabEditor);
    fSciShowWhitespace = new QCheckBox(tr("Show whitespace"), tabEditor);
    fSciTabWidth = new QLineEdit(tabEditor);
    fSciLongLineMark = new QCheckBox(tr("Long line marker:"), tabEditor);
    fSciLongLineSize = new QLineEdit(tabEditor);
    fSciTabWidth->setValidator(new QIntValidator(fSciTabWidth));
    ((QIntValidator*)fSciTabWidth->validator())->setRange(1, 80);
    fSciLongLineSize->setValidator(new QIntValidator(fSciLongLineSize));
    ((QIntValidator*)fSciLongLineSize->validator())->setRange(1, 9999);

    QGridLayout* layEditor = new QGridLayout(tabEditor);
    layEditor->setContentsMargins(8, 8, 8, 8);
    layEditor->setVerticalSpacing(4);
    layEditor->addItem(new QSpacerItem(10, 0, QSizePolicy::Maximum, QSizePolicy::Minimum), 1, 0);
    layEditor->addWidget(fSciMargin, 0, 0, 1, 2);
    layEditor->addWidget(fSciFolding, 1, 1);
    layEditor->addWidget(fSciLineNumbers, 2, 1);
    layEditor->addItem(new QSpacerItem(32, 0, QSizePolicy::Minimum, QSizePolicy::Minimum), 0, 2);
    layEditor->addWidget(fSciUseSpaces, 0, 3, 1, 2);
    layEditor->addWidget(fSciAutoIndent, 1, 3, 1, 2);
    layEditor->addWidget(fSciFont, 2, 3, 1, 2);
    layEditor->addItem(new QSpacerItem(0, 16, QSizePolicy::Minimum, QSizePolicy::Minimum), 3, 0, 1, 5);
    layEditor->addWidget(fSciIndentGuides, 4, 0, 1, 2);
    layEditor->addWidget(fSciShowWhitespace, 5, 0, 1, 2);
    layEditor->addWidget(new QLabel(tr("Tab Width:"), tabEditor), 4, 3);
    layEditor->addWidget(fSciTabWidth, 4, 4);
    layEditor->addWidget(fSciLongLineMark, 5, 3);
    layEditor->addWidget(fSciLongLineSize, 5, 4);
    fSciTabWidth->setMaximumWidth(40);
    fSciLongLineSize->setMaximumWidth(40);
    layEditor->addItem(new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding), 6, 5);
    tabs->addTab(tabEditor, tr("Text Editor"));

    // Lay out the dialog itself
    QGridLayout* dlgLayout = new QGridLayout(this);
    dlgLayout->setContentsMargins(4, 4, 4, 4);
    dlgLayout->setVerticalSpacing(4);
    dlgLayout->addWidget(tabs, 0, 0);
    QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel,
                                                     Qt::Horizontal, this);
    dlgLayout->addWidget(buttons, 1, 0);
    setFixedSize(sizeHint());
    setWindowTitle(tr("PlasmaShop Options"));

    // Populate the current/default settings
    QSettings settings("PlasmaShop", "PlasmaShop");
    fPrpEditorPath->setText(settings.value("PrpEditorPath", DEFAULT_PRP_EDITOR).toString());
    fVaultEditorPath->setText(settings.value("VaultEditorPath", DEFAULT_VAULT_EDITOR).toString());
    fSciMargin->setChecked(settings.value("SciMargin", true).toBool());
    fSciFolding->setChecked(settings.value("SciFoldMargin", true).toBool());
    fSciLineNumbers->setChecked(settings.value("SciLineNumberMargin", true).toBool());
    fSciUseSpaces->setChecked(settings.value("SciUseSpaces", true).toBool());
    fSciAutoIndent->setChecked(settings.value("SciAutoIndent", true).toBool());
    fSciIndentGuides->setChecked(settings.value("SciIndentGuides", false).toBool());
    fSciShowWhitespace->setChecked(settings.value("SciShowWhitespace", false).toBool());
    fSciLongLineMark->setChecked(settings.value("SciLongLineMark", false).toBool());
    fSciLongLineSize->setText(QString("%1").arg(settings.value("SciLongLineSize", 80).toInt()));
    fSciTabWidth->setText(QString("%1").arg(settings.value("SciTabWidth", 4).toInt()));

    QFont fnt;
    fnt.setFamily(settings.value("SciFont", PLAT_FONT).toString());
    fnt.setPointSize(settings.value("SciFontSize", 10).toInt());
    fnt.setWeight(settings.value("SciFontWeight", QFont::Normal).toInt());
    fnt.setItalic(settings.value("SciFontItalic", false).toBool());
    fSciFont->setFont(fnt);

    fSciFolding->setEnabled(fSciMargin->isChecked());
    fSciLineNumbers->setEnabled(fSciMargin->isChecked());
    fSciLongLineSize->setEnabled(fSciLongLineMark->isChecked());

    // Set up signals for the buttons
    connect(buttons, SIGNAL(accepted()), this, SLOT(onSave()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
    connect(browsePrpEditor, SIGNAL(clicked()), this, SLOT(onBrowsePrpEditor()));
    connect(browseVaultEditor, SIGNAL(clicked()), this, SLOT(onBrowseVaultEditor()));
    connect(fSciMargin, SIGNAL(clicked(bool)), fSciFolding, SLOT(setEnabled(bool)));
    connect(fSciMargin, SIGNAL(clicked(bool)), fSciLineNumbers, SLOT(setEnabled(bool)));
    connect(fSciLongLineMark, SIGNAL(clicked(bool)), fSciLongLineSize, SLOT(setEnabled(bool)));
    connect(fSciFont, SIGNAL(clicked()), this, SLOT(onSetFont()));
}

void OptionsDialog::onSave()
{
    // Validate everything *before* saving
    if (!QFile::exists(GetPSBinPath(fPrpEditorPath->text())) ||
        !QFileInfo(GetPSBinPath(fPrpEditorPath->text())).isFile()) {
        QMessageBox::critical(this, tr("Invalid Path"),
                              tr("You have entered an invalid path to your PRP editor."),
                              QMessageBox::Ok);
        return;
    }
    if (!QFile::exists(GetPSBinPath(fVaultEditorPath->text())) ||
        !QFileInfo(GetPSBinPath(fVaultEditorPath->text())).isFile()) {
        QMessageBox::critical(this, tr("Invalid Path"),
                              tr("You have entered an invalid path to your Vault editor."),
                              QMessageBox::Ok);
        return;
    }

    QSettings settings("PlasmaShop", "PlasmaShop");
    settings.setValue("PrpEditorPath", fPrpEditorPath->text());
    settings.setValue("VaultEditorPath", fVaultEditorPath->text());
    settings.setValue("SciMargin", fSciMargin->isChecked());
    settings.setValue("SciFoldMargin", fSciFolding->isChecked());
    settings.setValue("SciLineNumberMargin", fSciLineNumbers->isChecked());
    settings.setValue("SciUseSpaces", fSciUseSpaces->isChecked());
    settings.setValue("SciAutoIndent", fSciAutoIndent->isChecked());
    settings.setValue("SciIndentGuides", fSciIndentGuides->isChecked());
    settings.setValue("SciShowWhitespace", fSciShowWhitespace->isChecked());
    settings.setValue("SciLongLineMark", fSciLongLineMark->isChecked());
    settings.setValue("SciLongLineSize", fSciLongLineSize->text().toInt());
    settings.setValue("SciTabWidth", fSciTabWidth->text().toInt());
    settings.setValue("SciFont", fSciFont->font().family());
    settings.setValue("SciFontSize", fSciFont->font().pointSize());
    settings.setValue("SciFontWeight", fSciFont->font().weight());
    settings.setValue("SciFontItalic", fSciFont->font().italic());

    accept();
}

#ifdef Q_OS_WIN
    #define EXECFILTER "Executables (*.exe)"
#else
    #define EXECFILTER "All Files (*)"
#endif

void OptionsDialog::onBrowsePrpEditor()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select PRP Editor"),
                                                GetPSBinPath(fPrpEditorPath->text()),
                                                EXECFILTER);
    if (!path.isEmpty())
        fPrpEditorPath->setText(path);
}

void OptionsDialog::onBrowseVaultEditor()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Select Vault Editor"),
                                                GetPSBinPath(fVaultEditorPath->text()),
                                                EXECFILTER);
    if (!path.isEmpty())
        fVaultEditorPath->setText(path);
}

void OptionsDialog::onSetFont()
{
    fSciFont->setFont(QFontDialog::getFont(0, fSciFont->font(), this,
                                           tr("Select Editor Font")));
}


/* Path getter magic */
QString s_binBasePath;

QString GetPSBinPath(QString filename)
{
    return QDir(s_binBasePath).absoluteFilePath(filename);
}

QString GetPSDataPath(QString filename)
{
#ifdef Q_OS_WIN
    // Windows stores everything in Program Files
    return QDir(s_binBasePath).absoluteFilePath(filename);
#else
    // POSIX stores data in a separate location
    return QDir(DATA_PATH).absoluteFilePath(filename);
#endif
}
