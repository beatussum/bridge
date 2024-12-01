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


#ifndef BRIDGE_VISUALIZER_WIDGETS_LOGIN_DIALOG_HPP
#define BRIDGE_VISUALIZER_WIDGETS_LOGIN_DIALOG_HPP

#include "ui_LoginDialog.h"
#include <QtSql/QSqlDatabase>

/**
 * @file
 * @brief The header file of \ref LoginDialog
 */

namespace bridge::visualizer::widgets
{
    /**
     * @brief A dialog aiming to provide an easy way to connect to the database
     */

    class LoginDialog : public QDialog
    {
        Q_OBJECT

    public:
        /**
         * @brief Construct a new dialog with its parameters
         *
         * @param[in] __parent The parent of the dialog (it is a root widget if
         * this pointer is null)
         *
         * @param[in] __flags The window flags to set
         */

        LoginDialog(QWidget* __parent = nullptr, Qt::WindowFlags __flags = {});
    private:
        /**
         * @brief Gets the typed password
         *
         * @return The typed password
         */

        QString password() const
            { return m_ui->passwordLineEdit->text(); }

        /**
         * @brief Sets the typed password
         *
         * @param __password The password to set
         */

        void setPassword(const QString& __password)
            { m_ui->passwordLineEdit->setText(__password); }
    public:
        /**
         * @brief Gets the managed database
         *
         * @return The managed database
         */

        const QSqlDatabase& database() const noexcept
            { return m_database; }

        /**
         * @brief Gets the managed database
         *
         * @return The managed database
         */

        QSqlDatabase& database() noexcept
            { return m_database; }

        /**
         * @brief Gets the typed database name
         *
         * @return The typed database name
         */

        QString databaseName() const
            { return m_ui->databaseLineEdit->text(); }

        /**
         * @brief Sets the database name
         *
         * @param[in] __name The name to set
         */

        void setDatabaseName(const QString& __name);

        /**
         * @brief Gets the typed host
         *
         * @return The typed host
         */

        QString host() const
            { return m_ui->hostLineEdit->text(); }

        /**
         * @brief Set the host
         *
         * @param[in] __host The host to set
         */

        void setHost(const QString& __host);

        /**
         * @brief Gets the typed port
         *
         * @return The typed port
         */

        std::uint_fast16_t port() const
        {
            return
                static_cast<std::uint_fast16_t>(
                    m_ui->portSpinBox->value()
                );
        }

        /**
         * @brief Set the port
         *
         * @param[in] __port The port to set
         */

        void setPort(std::uint_fast16_t __port);

        /**
         * @brief Checks if custom host configuration should be used
         *
         * @return If custom host configuration should be used
         */

        bool customHostConfigEnabled() const
            { return m_ui->hostGroupBox->isChecked(); }

        /**
         * @brief Enables custom host configuration
         *
         * @param[in] __value If, and only if, this parameter is set to `true`,
         * the custom host configuration is enabled
         */

        void enableCustomHostConfig(bool __value = true)
            { m_ui->hostGroupBox->setChecked(__value); }

        /**
         * @brief Disables custom host configuration
         *
         * @param[in] __value If, and only if, this parameter is set to `true`,
         * the custom host configuration is disabled
         */

        void disableCustomHostConfig(bool __value = true)
            { enableCustomHostConfig(!__value); }

        /**
         * @brief Gets the typed username
         *
         * @return The typed username
         */

        QString username() const
            { return m_ui->usernameLineEdit->text(); }

        /**
         * @brief Sets the username
         *
         * @param[in] __username The username to set
         */

        void setUsername(const QString& __username)
            { m_ui->usernameLineEdit->setText(__username); }
    public slots:
        /**
         * @brief Opens the database
         */

        void openDatabase();

        /**
         * @brief Closes the database
         */

        void closeDatabase()
            { m_database.close(); }
    signals:
        /**
         * @brief Emited when the database name changes
         *
         * @param __name The new name
         */

        void databaseNameChanged(const QString& __name);

        /**
         * @brief Emitted when the host changes
         *
         * @param __host The new host
         */

        void hostChanged(const QString& __host);

        /**
         * @brief Emitted when the port changes
         *
         * @param __port The new port
         */

        void portChanged(std::uint_fast16_t __port);

        /**
         * @brief Emitted when the username changes
         *
         * @param __username The new username
         */

        void usernameChanged(const QString& __username);
    private:
        QSqlDatabase m_database; ///< The database managed by the dialog
        std::unique_ptr<Ui::LoginDialog> m_ui; ///< The UI object of the dialog
    };
}

#endif // BRIDGE_VISUALIZER_WIDGETS_LOGIN_DIALOG_HPP
