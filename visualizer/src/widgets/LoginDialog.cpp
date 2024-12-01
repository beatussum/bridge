/*
 * Copyright (C) 2024 Mattéo Rossillol‑‑Laruelle <beatussum@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <https://www.gnu.org/licenses/>.
 */


#include "widgets/LoginDialog.hpp"

namespace bridge::visualizer::widgets
{

    LoginDialog::LoginDialog(QWidget* __parent, Qt::WindowFlags __flags)
        : QDialog(__parent, __flags)
        , m_database(QSqlDatabase::addDatabase("QPSQL"))
        , m_ui(std::make_unique<Ui::LoginDialog>())
    {
        m_ui->setupUi(this);

        // signal forwarding

        QObject::connect(
            m_ui->databaseLineEdit,
            &QLineEdit::textChanged,
            this,
            &LoginDialog::databaseNameChanged
        );

        QObject::connect(
            m_ui->hostLineEdit,
            &QLineEdit::textChanged,
            this,
            &LoginDialog::hostChanged
        );

        QObject::connect(
            m_ui->portSpinBox,
            &QSpinBox::valueChanged,

            [&] (int __value) {
                emit portChanged(static_cast<std::int_fast16_t>(__value));
            }
        );

        QObject::connect(
            m_ui->usernameLineEdit,
            &QLineEdit::textChanged,
            this,
            &LoginDialog::usernameChanged
        );

        // handles the database state according to user inputs

        QObject::connect(
            this,
            &LoginDialog::databaseNameChanged,
            [&] (const QString& __name) { m_database.setDatabaseName(__name); }
        );

        QObject::connect(
            this,
            &LoginDialog::hostChanged,
            [&] (const QString& __host) { m_database.setHostName(__host); }
        );

        QObject::connect(
            this,
            &LoginDialog::portChanged,

            [&] (const std::int_fast16_t __port) {
                m_database.setPort(static_cast<int>(__port));
            }
        );

        // handles dialog buttons

        QObject::connect(
            m_ui->buttonBox,
            &QDialogButtonBox::clicked,

            [&] (QAbstractButton* __button) {
                switch (m_ui->buttonBox->standardButton(__button)) {
                    case QDialogButtonBox::Ok:
                        openDatabase();
                        break;

                    case QDialogButtonBox::Close:
                        close();
                        break;

                    default:
                        break;
                }
            }
        );
    }

    void LoginDialog::setDatabaseName(const QString& __name)
    {
        enableCustomHostConfig();
        m_ui->databaseLineEdit->setText(__name);
    }

    void LoginDialog::setHost(const QString& __host)
    {
        enableCustomHostConfig();
        m_ui->hostLineEdit->setText(__host);
    }

    void LoginDialog::setPort(std::uint_fast16_t __port)
    {
        enableCustomHostConfig();
        m_ui->portSpinBox->setValue(static_cast<int>(__port));
    }

    void LoginDialog::openDatabase()
    {
        if (!m_database.open(username(), password())) {
            throw std::runtime_error("`LoginDialog`: cannot open the database");
        }
    }
}
