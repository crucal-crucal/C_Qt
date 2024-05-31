#pragma once

#include "lib/uvmaterialcheckable.hpp"

class CUVMaterialCheckBoxPrivate;

class CUVMaterialCheckBox : public CUVMaterialCheckable {
	Q_OBJECT

public:
	explicit CUVMaterialCheckBox(QWidget* parent = nullptr);
	~CUVMaterialCheckBox() override;

private:
	Q_DISABLE_COPY(CUVMaterialCheckBox)
	Q_DECLARE_PRIVATE(CUVMaterialCheckBox)
};
