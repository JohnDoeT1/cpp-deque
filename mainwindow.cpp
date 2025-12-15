#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

#include <QMessageBox>
#include <algorithm>
#include <cctype>
#include <climits>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    deque_model_.random_gen = random_gen;
}

void MainWindow::ApplyModel() {
    auto it_tmp = deque_model_.iterator;

    ui->list_widget->clear();
    for (size_t i = 0; i < deque_model_.items.size(); ++i)
    {
        ui->list_widget->addItem(
            QString::number(i) + ": " +
            QString::fromStdString(deque_model_.items[i])
            );
    }
    ui->list_widget->addItem("end");

    deque_model_.iterator = it_tmp;
    ApplyIterator();

    bool empty = deque_model_.items.empty();
    ui->btn_pop_back->setEnabled(!empty);
    ui->btn_pop_front->setEnabled(!empty);
    ui->txt_size->setText(QString::number(deque_model_.items.size()));
}

void MainWindow::ApplyIterator() {
    if (deque_model_.iterator > deque_model_.items.end()) {
        deque_model_.iterator = deque_model_.items.end();
    }

    int row = static_cast<int>(
        std::distance(deque_model_.items.begin(), deque_model_.iterator)
        );

    ui->list_widget->setCurrentRow(row);

    bool at_end = (deque_model_.iterator == deque_model_.items.end());
    bool at_begin = (deque_model_.iterator == deque_model_.items.begin());

    ui->btn_edit->setDisabled(at_end);
    ui->btn_erase->setDisabled(at_end);
    ui->btn_dec_iterator->setDisabled(at_begin);
    ui->btn_inc_iterator->setDisabled(at_end);

    if (at_end)
    {
        ui->txt_elem_content->clear();
        ui->txt_elem_content->setDisabled(true);
    } else
    {
        ui->txt_elem_content->setDisabled(false);
        ui->txt_elem_content->setText(
            QString::fromStdString(*deque_model_.iterator)
            );
    }
}

// ---------- ЗАГОТОВКИ ----------
void MainWindow::on_btn_tea_clicked() {
    static std::deque<std::string> tea = {
        "Чай Лунцзин",
        "Эрл Грей",
        "Сенча",
        "Пуэр",
        "Дарджилинг",
        "Ассам",
        "Матча",
        "Ганпаудер",
        "Оолонг",
        "Лапсанг Сушонг"
    };

    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_cakes_clicked() {
    static std::deque<std::string> cakes = {
        "Красный бархат",
        "Наполеон",
        "Медовик",
        "Тирамису",
        "Прага",
        "Чизкейк",
        "Захер",
        "Эстерхази",
        "Морковный торт",
        "Чёрный лес"
    };

    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

// ---------- РЕДАКТИРОВАНИЕ / ПОИСК ----------
void MainWindow::on_btn_edit_clicked() {
    if (deque_model_.iterator != deque_model_.items.end())
    {
        *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
        ApplyModel();
    }
}

void MainWindow::on_btn_find_clicked() {
    auto value = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator =
        std::find(
            deque_model_.items.begin(),
            deque_model_.items.end(),
            value
            );
    ApplyIterator();
}

void MainWindow::on_btn_count_clicked() {
    auto value = ui->le_count->text().toStdString();
    int cnt = std::count(
        deque_model_.items.begin(),
        deque_model_.items.end(),
        value
        );
    ui->lbl_count->setText(QString::number(cnt));
}

// ---------- MIN / MAX ----------
void MainWindow::on_btn_min_element_clicked() {
    if (deque_model_.items.empty())
    {
        deque_model_.iterator = deque_model_.items.end();
    } else
    {
        deque_model_.iterator =
            std::min_element(
                deque_model_.items.begin(),
                deque_model_.items.end()
                );
    }
    ApplyIterator();
}

void MainWindow::on_btn_max_element_clicked() {
    if (deque_model_.items.empty())
    {
        deque_model_.iterator = deque_model_.items.end();
    } else
    {
        deque_model_.iterator =
            std::max_element(
                deque_model_.items.begin(),
                deque_model_.items.end()
                );
    }
    ApplyIterator();
}


// ---------- ДЕК ----------
void MainWindow::on_btn_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_push_front_clicked() {
    auto text = ui->txt_elem_content->text();
    if (!text.isEmpty())
    {
        deque_model_.items.push_front(text.toStdString());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::on_btn_push_back_clicked() {
    auto text = ui->txt_elem_content->text();
    if (!text.isEmpty())
    {
        deque_model_.items.push_back(text.toStdString());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::on_btn_pop_back_clicked() {
    if (!deque_model_.items.empty())
    {
        deque_model_.items.pop_back();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::on_btn_pop_front_clicked() {
    if (!deque_model_.items.empty())
    {
        deque_model_.items.pop_front();
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::on_btn_insert_clicked() {
    auto value = ui->txt_elem_content->text().toStdString();
    if (!value.empty())
    {
        deque_model_.items.insert(deque_model_.iterator, value);
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

void MainWindow::on_btn_erase_clicked() {
    if (deque_model_.iterator != deque_model_.items.end())
    {
        deque_model_.items.erase(deque_model_.iterator);
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}

// ---------- ИТЕРАТОР ----------
void MainWindow::on_btn_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_btn_dec_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.begin())
    {
        --deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::on_btn_inc_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.end())
    {
        ++deque_model_.iterator;
        ApplyIterator();
    }
}

// ---------- АЛГОРИТМЫ ----------
void MainWindow::on_btn_merge_sort_clicked() {
    deque_model_.items = MergeSort(
        deque_model_.items,
        std::less<std::string>()
        );
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_merge_sOrT_clicked() {
    auto comp = [](const std::string& a, const std::string& b) {
        return std::lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end(),
            [](char x, char y) {
                return std::tolower(x) < std::tolower(y);
            }
            );
    };

    deque_model_.items = MergeSort(deque_model_.items, comp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_shuffle_clicked() {
    auto it_tmp = deque_model_.iterator;
    std::shuffle(
        deque_model_.items.begin(),
        deque_model_.items.end(),
        deque_model_.random_gen
        );
    deque_model_.iterator = it_tmp;
    ApplyModel();
}

void MainWindow::on_btn_unique_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end()))
    {
        ui->lbl_count->setText("Дек не отсортирован");
        return;
    }

    auto last = std::unique(
        deque_model_.items.begin(),
        deque_model_.items.end()
        );
    deque_model_.items.erase(last, deque_model_.items.end());
    deque_model_.iterator = deque_model_.items.begin();
    ui->lbl_count->clear();
    ApplyModel();
}

void MainWindow::on_btn_reverse_clicked() {
    if (deque_model_.items.empty())
    {
        return;
    }

    // Сохраняем индекс текущего элемента
    auto it_index = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    bool at_end = (deque_model_.iterator == deque_model_.items.end());

    // реверс порядка элементов в деке
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());

    // Восстанавливаем итератор по индексу
    if (at_end)
    {
        deque_model_.iterator = deque_model_.items.end();
    } else
    {
        deque_model_.iterator = deque_model_.items.begin() + it_index;
    }

    ApplyModel();
}


void MainWindow::on_btn_lower_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end()))
    {
        ui->lbl_count->setText("Дек не отсортирован");
        return;
    }

    ui->lbl_count->clear();
    auto value = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator =
        std::lower_bound(
            deque_model_.items.begin(),
            deque_model_.items.end(),
            value
            );
    ApplyIterator();
}

void MainWindow::on_btn_upper_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end()))
    {
        ui->lbl_count->setText("Дек не отсортирован");
        return;
    }

    ui->lbl_count->clear();
    auto value = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator =
        std::upper_bound(
            deque_model_.items.begin(),
            deque_model_.items.end(),
            value
            );
    ApplyIterator();
}

// ---------- РАЗМЕР ----------
void MainWindow::on_btn_resize_clicked() {
    bool ok;
    int new_size = ui->txt_size->text().toInt(&ok);

    if (!ok || new_size < 0 || new_size > 1000)
    {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Размер должен быть от 0 до 1000"
            );
        return;
    }

    auto it_tmp = deque_model_.iterator;
    deque_model_.items.resize(new_size);
    deque_model_.iterator = it_tmp;
    ApplyModel();
}

// ---------- ВЫБОР ----------
void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    currentRow = std::clamp(
        currentRow,
        0,
        static_cast<int>(deque_model_.items.size())
        );

    if (static_cast<size_t>(currentRow) == deque_model_.items.size())
    {
        deque_model_.iterator = deque_model_.items.end();
    } else
    {
        deque_model_.iterator = deque_model_.items.begin() + currentRow;
    }

    ApplyIterator();
}
